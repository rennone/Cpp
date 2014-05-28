#include <iostream>
using namespace std;

class Hoge;
class Foo
{  
  Hoge *hoge;
public:
  Foo();
  Hoge& getHoge();
};

class Hoge
{
  Hoge(const Hoge&);
  Hoge& operator=(const Hoge &);
public:
  Hoge()
  {
    cout << "Hoge" << endl;
  }
  ~Hoge()
  {
    cout << "Hoge des" << endl;
  }
  void print()
  {
    cout << "hoge print" << endl;
  }  
};

class HogeChild : public Hoge
{
public:
  HogeChild():Hoge()
  {
  }
  
  void printChild()
  {
    cout << "Hoge Child" << endl;
  }
};

Foo::Foo()
{
  hoge = new HogeChild();
}

Hoge& Foo::getHoge()
{
  return *hoge;
}

void del(Foo &foo)
{
  HogeChild &hoge = (HogeChild &)foo.getHoge();
  hoge.printChild();
}

int main()
{
  Foo foo;
  Hoge &hoge = foo.getHoge();
  Hoge hoge2;
//  hoge2 = hoge;
  del(foo);
  hoge.print();

  return 0;
}
