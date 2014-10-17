#include <iostream>
using namespace std;

//関数内スタティック変数もクラスでただ１つしか生成されない.
class Hoge
{
public:
  void print()
  {
    static int a = 0;
    cout << a++ << endl;
  }
};
  
int main()
{

  Hoge h1,h2;

  h1.print();
  h1.print();

  h2.print();
}
