/*
メンバ関数内のstatic変数は, 各実体で共有されるのかテスト

結論 -> される.クラス変数とおなじで, すべてのインスタンスから同じ
しかも, 継承した子クラス全てで共有される(virtualでは試してないけど, 意味ないし).
Aのローカルで宣言
B:public A
C:public A

B b;
C c;
bで設定 -> cでも変更される
 */

class Hoge
{
public:
  Hoge() {  }
  int getStatic()
  {
    return sta();    
  }

  void setStatic(const int i)
  {
    sta() = i;    
  }
private:
  int& sta()
  {
    static int i=0;
    return i;    
  }
  
};

class Piyo: public Hoge
{
public:
  Piyo()
  {
  }
  
};

class Foo: public Hoge
{
public:
  Foo()
  {
  }  
}; 


#include <iostream>
using namespace std;

int main()
{
  Piyo t;
  Foo  u;
  t.setStatic(5);
  cout << u.getStatic() << endl;
  u.getStatic() = 4;
  return 0;  
}


  
