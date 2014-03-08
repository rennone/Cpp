
#include "initMemberTest.h"


Hoge::Hoge(const float &a, const float &b, const float &c)
  :a(a), b(b), c(c)
{
  cout << a << "," << b << "," << c << endl;
}

int main()
{
  float a = 2;
  float b = 3;
  float c = 4;
  Hoge(a,b,c);
  return 0;
}
