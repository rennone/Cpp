#include<iostream>
#include<fstream>
using namespace std;
double w1,w2,w3;
const double nu = 0.05;
int t = 0;
ofstream ofs("weight.txt");

bool learning(double,double,int);
double judge(double, double);
void printWeight();

bool learning(double x1, double x2, int t){
  int o = judge(x1,x2);
  if(o==t) return false;
  double d = t-o;

  w1 = w1 + nu*d*x1;
  w2 = w2 + nu*d*x2;
  w3 = w3 + nu*d;
  printWeight();
  return true;
}

double judge(double x1, double x2){
  if( w1*x1 + w2*x2 + w3 < 0)
    return -1;
  else
    return 1;
}

void printWeight(){
  ofs << t << " " << w1 << " " << w2 << " " << w3 << endl;
  t++;
}

int main(){
  w1 = w2 = w3 = 0.5; //初期値 
  float x1, x2;
  int t;
  
  double X1[61], X2[61];
  int T[61];
  for(int i=0; i<60; i++)
    cin >> X1[i] >> X2[i] >> T[i];  //データを取ってくる 

  printWeight();
  int jnum=1;
  while(jnum!=0){
    jnum = 0;
    for(int i=0;i<60;i++){
      jnum += learning(X1[i], X2[i], T[i]);
    }
    cout << "jnum " << jnum << endl;
  }
  
  jnum = 0;
  for(int i=0; i<60; i++)
    if(judge(X1[i],X2[i]) != T[i])    jnum++; //間違えた個数
  
  cout << "after" << jnum << endl;

  cout << -w1/w2 << "*x+" << -w3/w2 << endl; 
}
