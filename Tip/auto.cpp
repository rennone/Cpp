
class Foo
{
  int x;
public:
  Foo(int _x):x(_x) {}
};

class HogeAuto
{
  static constexpr int num = 10;
  Foo *foos[num];
public:
  Hoge()
  {

    for(auto foo : foos)
    {
      foo = new Foo(0);
      //fooはあくまでローカル変数なので, fooを返したりしては行けない
      return foo;
    }
  }
};

class HogeIndex
{
  static constexpr int num = 10;
  Foo *foos[num];
public:
  Hoge()
  {
    for(int i=0; i<num; i++)
    {
      foos[i] = new Foo(0);
      //foos[i]を返すのはok
      return foos[i]; 
    }
  }
};


