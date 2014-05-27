#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

class Spline {
  int num;
  double h;
  double *x;
  double *a, *b, *c, *d;
public:
  Spline(const map<double, double> &data);
  double calc(double t);
};

Spline::Spline(const map<double, double> &data)
{
  num = data.size();
  
  x = new double[num];
  a = new double[num];  
  b = new double[num];
  c = new double[num];
  d = new double[num];
  
  double *w = new double[num+1];
  
  //xの範囲を取得
  int k=0;
  for(auto elem : data)
  {
    x[k] = elem.first;
    a[k] = elem.second;
    k++;
  }

  c[0] = c[num-1] = 0;
  for(int i=1; i<num-1; i++)
  {
    c[i] = 3.0 * (a[i-1] - 2.0 * a[i] + a[i+1]);
  }
  
  w[0] = 0;
  for(int i=1; i<num; i++)
  {
    double tmp = 4.0 - w[i-1];
    c[i] = (c[i] - c[i-1])/tmp;
    w[i] = 1.0/tmp;
  }  
    // 右上を消す
  for(int i=num-1; i>0; i--) {
    c[i] = c[i] - c[i+1] * w[i];
  }

  // ３次多項式の1次係数(b)と3次係数(b)を計算
  b[num-1] = d[num-1] =0.0;
  for(int i=0; i<num; i++) {
    double h = x[i+1] - x[i];
    d[i] = ( c[i+1] - c[i]) / 3.0;
    b[i] = (a[i+1] - a[i]) - c[i] - d[i];
  }

  delete[] w;
}

// Ｂスプライン描画
// x[num], y[num]は座標の配列
//媒介変数(0～num-1の実数）に対する値を計算
double Spline::calc(double _x)
{
  double t = (_x-x[0])/(x[1]-x[0]);
  int j;
  double dt;
  j = (int)floor(t); // 小数点以下切捨て
  if(j < 0)
    j=0;
  else if (j >= num)
    j=num-1; // 丸め誤差を考慮

  dt = t - (double)j;
  return a[j] + ( b[j] + (c[j] + d[j] * dt) * dt ) * dt;
}

int main()
{
  ifstream ifs("XYZtable.txt");
  map<double, double> dataR, dataG, dataB, dataS;
  while(ifs)
  {
    double l,r,g,b,s;
    ifs >> l >> r >> g >> b >> s;
    dataR.insert({l, r});
    dataG.insert({l, g});
    dataB.insert({l, b});
    dataS.insert({l, s});
  }

  Spline *R = new Spline(dataR);
  Spline *G = new Spline(dataG);
  Spline *B = new Spline(dataB);
  Spline *S = new Spline(dataS);

  ofstream ofs("newXYZTable.csv");
  for(int i=360; i < 800; i++)
  {
    ofs << i << "," << R->calc(i) << "," << G->calc(i) << ","  << B->calc(i) << "," << S->calc(i) << endl;
  }
}
