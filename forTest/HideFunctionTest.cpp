#include <iostream>
using namespace std;

/*
virtual関数に対し,戻り値の型だけが異なる関数でオーバーライドしたばあい

Parent *c = new Child()
c->func();
としたときに, 呼び出される関数はparentとChildどっちで定義した関数が呼び出されるか
-> Childの方が呼び出される
*/

class Hoge
{
public:
  virtual void func()
  {
    cout << "hoge" << endl;    
  }
  
};


class HogeChild:public Hoge
{
public:
  void func()
  {
    cout << "hogeChild" << endl;    
  }
};


class HaveHoge
{  
  Hoge *hoge;  
public:
  HaveHoge()
  {
    hoge = new Hoge();    
  }

  //引数の型はHoge
  virtual Hoge* getHoge()
  {
    return hoge;    
  }
  
};

class HaveHogeChild: public HaveHoge
{
  Hoge *hogeChild;  
public:
  HaveHogeChild()
  {
    hogeChild = new HogeChild();    
  }

  //引数の方はHogeChild
  HogeChild* getHoge()
  {
    return (HogeChild*)hogeChild;    
  }  
};


int main()
{
  HaveHoge *h = new HaveHoge();
  h->getHoge()->func();

  HaveHoge *hc = new HaveHogeChild();

  hc->getHoge()->func();
  
}


 
  

  
