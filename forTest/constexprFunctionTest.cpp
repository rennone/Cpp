#include <iostream>

using namespace std;
constexpr int evaluate(const int &val)
{
  return val*2;
}

int main()
{
  cout << evaluate(5) << endl;

  
  int a = 3;
  cin >> a;
  cout << evaluate(a) << endl;  
}
