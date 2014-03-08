class Hoge
{
public:
  int a;
  Hoge()
  {
    a=0;
  }
};


#include <iostream>
using namespace std;
int main()
{
  Hoge p;
  p.a = 10;
  p = Hoge();
  cout << p.a << endl;
  return 0;
}
