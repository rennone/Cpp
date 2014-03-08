#include <iostream>
using namespace std;

class Hoge
{
public:
  class Piyo
  {
  public:
    int a;
    Piyo()
    {
      a = 10;
    }
  };

  Hoge():p(new Piyo())
  {
  }

  Piyo* getPiyo()
  {
    return p;
  }

  
  Piyo* const& getPiyo2()
  {
    return p;
  }

  Piyo*& getPiyo3()
  {
    return p
  }

private:
  Piyo* const p;
};

int main()
{
  Hoge h;
  Hoge::Piyo *p = h.getPiyo();
  p->a = 20;  
  
  p = new Hoge::Piyo();  //hの法は書き変わらない(あくまでpの示すアドレスが変わるだけ)
  cout << "h = " << h.getPiyo()->a << endl;
  cout << "p = " << p->a << endl;

  Hoge::Piyo *q = new Hoge::Piyo();

  //h.getPiyo3() = q;  //hの方のアドレスが書き変わる h.p にconstがついているとエラー
  
  cout << "q = " << q->a << endl;
  cout << "h = " << h.getPiyo()->a << endl;
  return 0;
}
