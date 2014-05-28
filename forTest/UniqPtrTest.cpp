#include <iostream>
#include <memory>
using namespace std;

class Hoge
{
public:
  Hoge()
  {
    h = 0;
    cout << "Cons" << endl;
  }
  ~Hoge()
  {
    cout << "Dest" << endl;
  }
  int h;
};
  
int main()
{
  Hoge *hoge = new Hoge();
  unique_ptr<Hoge> h = unique_ptr<Hoge>(hoge);
  cout << h.get() << endl;
  cout << hoge << endl;
  h = unique_ptr<Hoge>(hoge);
  
  int a;
//  delete hoge;
  cin >> a;
  return 0;
}
