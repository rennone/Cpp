#include<math.h>
#include<complex>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<direct.h>
using namespace std;

typedef complex<double> Complex;

class NTFAnalyze{
  double b, y;
  int N;

  double a;  //ラメラの幅
  double d; //ラメラの厚さ
  int M;    //レイヤの数
  double thera_rad; //入射角
  double lambda;    //波長
  double K; //波数  
  static constexpr double ToRad = M_PI/180.0;
public:
  //d: 厚さ
  //M: レイヤ数
  NTFAnalyze(double _d, int _M)
    :d(_d), M(_M)
  {
    N = 1;
    b = 900*pow(10,-9.0);
    y = 0;
    a = 300*pow(10,-9.0);   
  }

  void setM(int _M){
    M = _M;
  }

  double* calcRefrac(double lambda, int theta)
  {
    K = k(lambda);
    theta_rad = theta*ToRad;
    
    double *data = new double[360];
    double rad_theta = theta*ToRad;
    
    double sum=0;
    for(int phi=-90; phi < 270; phi++){
      double rad_phi = phi*ToRad;			//90度ずらす
      data[phi+90] = I(lambda, rad_theta, rad_phi);	//theta: 入射角, phi:反射角
      sum += data[phi+90];
    }
    
    return data;
  }

  void calcI(double phi_rad)
  {
    double u = sin(theta) + sin(phi);
    double v = cos(theta) + cos(phi);

    if( u == 0 || v == 0) 
      return 0.5*( calcI(phi_rad + 0.01*ToRad) + calcI(phi_rad - 0.01*ToRad) );
    
    double kdv = K*d*v;
    double kau = K*a*u);
    double _sin1 = pow( sin(kdv*M/2), 2.0);
    double _sin2 = pow( sin(kdv  /2), 2.0);
    double _sin3 = pow( sin(kau  /2), 2.0);
    double _cos1 = pow( cos(theta  ), 2.0);
    double _a = a*a/2;
    double _b = pow(kau, 2.0);

    return _a * (_sin1 / _sin2) * (_sin3 / _b) * F(theta, phi) * I(theta)*_cos1);
  }
  
  
  void output(double lambda, int theta){

    ofstream ofp(dir + to_s(theta) + "deg"+to_s(lambda*pow(10,9.0)) + "nm.txt");
    ofp.setf(ios::fixed, ios::floatfield);	//固定小数点, 20桁制度で指定
    ofp.precision(20);
		
    double data[360];
    double sum=0;
    double rad_theta = theta*M_PI/180.0;

    for(int phi=-90; phi < 270; phi++){
      double rad_phi = phi*M_PI/180.0;			//90度ずらす
      data[phi+90] = I(lambda, rad_theta, rad_phi);	//theta: 入射角, phi:反射角
      sum += data[phi+90];
    }

    for(int i=0; i<360; i++)
      ofp << data[i]/sum << endl;
  }

private:
  double k(double l){
    return 2*M_PI/l;
  }

  double u(double theta, double phi){
    return sin(theta) + sin(phi);
  }

  double v(double theta, double phi){
    return cos(theta) + cos(phi);
  }

  double psi(double theta, double phi){
    return K*y*v(theta, phi);
  }

  static constexpr double I(double theta){
    return 1.0e-6;
  }

  double I(double l, double theta, double phi){
    //分母が0になるときは少しずらして近似
    if(u(theta, phi) == 0 || v(theta, phi) == 0) 
      return 0.5*( I(l, theta, phi + 0.01*ToRad) + I(l, theta, phi - 0.01*ToRad) );

    double kdv = K*d*v(theta, phi);
    double kau = K*a*u(theta, phi);
    double _sin1 = pow( sin(kdv*M/2), 2.0);
    double _sin2 = pow( sin(kdv  /2), 2.0);
    double _sin3 = pow( sin(kau  /2), 2.0);
    double _cos1 = pow( cos(theta  ), 2.0);
    double _a = a*a/2;
    double _b = pow(kau, 2.0);

    return _a * (_sin1 / _sin2) * (_sin3 / _b) * F(theta, phi) * I(theta)*_cos1);
  }

  double F(double theta, double phi){
    int n = 1;
    Complex fr = polar(1.0, K*b*u(theta,phi)*n + psi(theta, phi) );
    return norm( fr );
  }
};

int main(){
  double d,t,m;
  cout << "(d, m) =";
  cin >> d >> m;
  NTFAnalyze *sol = new NTFAnalyze(d*pow(10,-9.0), m);

  for(int theta = -90; theta < 90; theta+=10){
    for(int i=380; i<700; i+=5){
      sol->output(1.0*i*pow(10,-9.0), theta);
    }
  }
  return 0;
}
