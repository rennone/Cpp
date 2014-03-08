#include <iostream>
using namespace std;

class Hoge
{
public:
  virtual void func()
  {
    cout << "hoge" << endl;    
  }

  Hoge()
  {
    cout << "hoge constructa" << endl;    
  }

  virtual ~Hoge()
  {
    cout << "hoge destructa" << endl;
  }

  virtual void test(Hoge* h)
  {
    cout << "asd";
    h->func();    
  }
  
};


class Piyo : public Hoge
{
public:
  void func()
  {
    cout << "piyo" << endl;    
  }
  Piyo()
    :Hoge()
  {
    cout << "piyo constructa" << endl;    
  }
  ~Piyo()
  {
    cout << "piyo destructa" << endl;
  }  
  
};

#include <memory>
auto_ptr<Hoge> createHoge()
{
  return auto_ptr<Hoge>(new Hoge());  
}

auto_ptr<Hoge> createPiyo()
{
  return auto_ptr<Hoge>(new Piyo());  
}

void test()
{
  auto h = createHoge();
  h->func();

  auto p = createPiyo();

  Piyo *a = new Piyo();
  
  h->test(p);
  
//  ( (auto_ptr<Piyo>)p)->func();
}

int main()
{

  test();
  int t;  
  
  cin >> t;
  
  return 0;  
}




  
  
