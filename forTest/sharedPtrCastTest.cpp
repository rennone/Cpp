/* shared_ptrのキャストのテスト*/

#include <iostream>
#include <memory>
using namespace std;

class Parent
{
public:
  shared_ptr<Parent> c;
  Parent()
  {
  }
  virtual ~Parent()
  {
  }

  void hoge()
  {
    cout << "Parent" << endl;
  }  
};

class Child : public Parent
{
public:
  Child()
    :Parent()
  {
  }
  ~Child()
  {
  }
  void hoge()
  {
    cout << "child" << endl;
  }
};

int main()
{
  auto pa = make_shared<Parent>();

  pa->c = make_shared<Child>();

  auto c = dynamic_pointer_cast<Child>(pa->c);
  c->hoge();

  pa->c->hoge();
  
}
