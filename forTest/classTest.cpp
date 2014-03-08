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
      a = 1;
    }
  };

  Hoge()
  {
    p.a = 0;
  }

  Piyo& getPiyo()
  {
    return p;
  }
private:
  Piyo p;
};

int main()
{
  Hoge h;

  cout << h.getPiyo().a << endl;
  
  return 0;
}
