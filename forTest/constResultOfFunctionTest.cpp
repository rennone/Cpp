
class Hoge
{
public :
  const bool equal5(const int &x) const
  {
    return x == 5;
  }
};

#include <iostream>
using namespace std;
int main()
{
  Hoge h;

  bool res = h.equal5(0);

  cout << res << endl;
  res = true;
  cout << res << endl;
}

  
