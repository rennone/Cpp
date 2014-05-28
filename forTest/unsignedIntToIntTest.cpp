#include <iostream>
using namespace std;

void foo(const unsigned int &a)
{
  cout << a << endl;
  cout << (a<8) << endl;
}

int main()
{
  int i = 0;
  foo(i);
  i = 10;
  foo(i);
  i = -1;
  foo(i);
  
  return 0;
}
