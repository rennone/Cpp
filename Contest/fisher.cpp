#include<iostream>
#include<complex>
using namespace std;

class Mat3;
class Vec3;

class Vec3{
public:
  double x,y,z;
  Vec3():x(0),y(0),z(0){}
  Vec3(double a, double b):x(a),y(b),z(1){}
  Vec3(double a, double b, double c):x(a),y(b),z(c){}

  void normalize(){
    double A = x*x + y*y + z*z;
    if(A == 0) return;
    x /=A;
    y /=A;
    z /=A;
  }
};

Vec3 operator+(const Vec3 &a, const Vec3 &b){
  return Vec3(a.x+b.x, a.y+b.y, a.z+b.z);
};

Vec3 operator-(const Vec3 &a, const Vec3 &b){
  return Vec3(a.x-b.x, a.y-b.y, a.z-b.z);
};

template<class T> Vec3 operator*(const T &s, const Vec3 &A){
  return Vec3(s*A.x, s*A.y, s*A.z);
};

template<class T> Vec3 operator/(const Vec3 &A, const T s){
  return Vec3(A.x/s, A.y/s, A.z/s);
};

class Mat3{
public:
  double a[3][3];
  Mat3(){
    for(int i=0;i<3; i++)
      for(int j=0; j<3; j++)
	a[i][j] = 0;
  }  
  Mat3(double _a11, double _a12, double _a13,
       double _a21, double _a22, double _a23,
       double _a31, double _a32, double _a33){
    a[0][0] = _a11;    a[0][1] = _a12;    a[0][2] = _a13;
    a[1][0] = _a21;    a[1][1] = _a22;    a[1][2] = _a23;
    a[2][0] = _a31;    a[2][1] = _a32;    a[2][2] = _a33;
  }
  
  Mat3(double x[3][3]){
    for(int i=0; i<3; i++)
      for(int j=0; j<3; j++)
	a[i][j] = x[i][j];
  }
  
  Mat3(const Vec3 &A){
    a[0][0] = A.x*A.x;
    a[0][1] = a[1][0] = A.x*A.y;
    a[0][2] = a[2][0] = A.x*A.z;
    a[1][1] = A.y*A.y;
    a[1][2] = a[2][1] = A.y*A.z;
    a[2][2] = A.z*A.z;
  }
  double miniDat(int i, int j){
    int l = (i==0 ? 1 : 0);
    int r = (i==2 ? 1 : 2);
    int t = (j==0 ? 1 : 0);
    int b = (j==2 ? 1 : 2);
    int sign = ((i+j)%2==0 ? 1 : -1);
    return sign*(a[l][t]*a[r][b] - a[r][t]*a[l][b]);
  };

  double dat(){
    return a[0][0]*a[1][1]*a[2][2] + a[0][1]*a[1][2]*a[2][0] + a[0][2]*a[1][0]*a[2][1]
         - a[0][2]*a[1][1]*a[2][0] - a[0][1]*a[1][0]*a[2][2] - a[0][0]*a[1][2]*a[2][1];
  }
  
  //逆行列
  Mat3 inverse(){
    double A = dat();
    if(A == 0){
      cout << "not exist" << endl;
      printMat();
      return Mat3(0,0,0,0,0,0,0,0,0);
    }
    double x[3][3];
    for(int i=0; i<3;i++)
      for(int j=0; j<3; j++)
	x[i][j] = miniDat(i,j)/A;
    Mat3 inv = Mat3(x); 
    return inv;
  }

  Mat3 inverse2(){
    double A = miniDat(2,2);
    if(A==0){
      cout << "not exist" << endl;
      printMat();
      return Mat3(0,0,0,0,0,0,0,0,0);
    }

    Mat3 inv = Mat3(a[1][1]/A, -a[0][1]/A, 0.0,
		    -a[1][0]/A,  a[0][0]/A, 0.0,
		    0.0, 0.0, 1.0);
    return inv;
  }
  //転置行列 
  Mat3 transpose(){
    double x[3][3];
    for(int i=0; i<3;i++)
      for(int j=0; j<3; j++)
	x[i][j] = a[j][i];
    Mat3 trs = Mat3(x);
    return trs;
  }

  void printMat(){
    for(int i=0; i<3; i++){
      for(int j=0;j<3; j++){
	cout << a[i][j] << " " << flush;
      }
      cout << endl;
    }
  }
};

Mat3 operator+(const Mat3 &A,const Mat3 &B){
  double x[3][3];
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      x[i][j] = A.a[i][j] + B.a[i][j];
  Mat3 C = Mat3(x);
  return C;
}

Mat3 operator*(const double &s, const Mat3 &A){
  double x[3][3];
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      x[i][j] = s*A.a[i][j];
  Mat3 B = Mat3(x);
  return B;
}

Mat3 operator*(const Mat3 &A, const Mat3 &B){
  double x[3][3];
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      x[i][j] = A.a[i][0]*B.a[0][j] + A.a[i][1]*B.a[1][j] + A.a[i][2]*B.a[2][j];
    }
  }
  Mat3 C = Mat3(x);
  return C;
}

Mat3 operator/(const Mat3 &A, const double s){
 double x[3][3];
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      x[i][j] = A.a[i][j]/s;
  Mat3 B = Mat3(x);
  return B;
}

Vec3 operator*(const Mat3 &A, const Vec3 v){
  double x[3];
  for(int i=0; i<3; i++)
    x[i] = A.a[i][0]*v.x * A.a[i][1]*v.y + A.a[i][2]*v.z;

  return Vec3(x[0], x[1], x[2]);
}

double w1,w2,w3;
int n;
Mat3 Sw, Sb;
double s1, s2;
int T[61];
int m1,m2;
Vec3 ave1,ave2;
Vec3 X[100];


int main(){
  cin >> n;
  m1 = m2 = 0;
  ave1 = ave2 = Vec3();  

  for(int i=0; i<n; i++){
    double x,y;
    cin >> x >> y >> T[i];
    X[i] = Vec3(x,y,0);
    if(T[i] == 1){
      m1++;
      ave1 = ave1 + X[i];
    }
    else{
      m2++;
      ave2 = ave2 + X[i];
    }
  }  
  ave1 = ave1/m1;
  ave2 = ave2/m2;
  Sb = Mat3(ave1 - ave2);
    
  for(int i=0; i<n; i++){
    if(T[i]==1) 
      Sw = Sw + Mat3(X[i] - ave1);
    else
      Sw = Sw + Mat3(X[i] - ave2);
  }
  Sw = Sw/(double)(m1+m2);

  Sw.printMat();
  Mat3 inv = Sw.inverse2();
  Mat3 E = inv*Sw;
  E.printMat();
  Vec3 w = inv*(ave1-ave2);
  w.normalize();
  cout << w.x << " " << w.y << " " << w.z << endl;
  Vec3 m = 0.5*(ave1 + ave2);
  w.z = -w.x*m.x - w.y*m.y; //中点を通るように定数項を変更 
  cout << -w.x/w.y << "*x+" << -w.z/w.y << endl; 
}

