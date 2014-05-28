#include <iostream>

class Single
{
  int a = 0;

  Single()
  {
    std::cout << "Single Const" << std::endl;
  };
  Single(const Single &other);
  Single& operator=(const Single &other);
  public:
  Single(const Single &&other)
  {
    this->a = std::move(other.a);
  }
  static Single& getInstance()
  {
    static Single instance;
    return instance;
  }

  void print()
  {
    std::cout << a << std::endl;
  }
};


int main()
{
  Single &a = Single::getInstance();
//  Single b;
//  Single c(Single::getInstance());
//  Single d = a;
  Single e(std::move(a));
  
  a.print();
}
