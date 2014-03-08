//const vector<T> だと, どこが変更されない事が保証されるのかを確認

//中身の方は保証されているっぽい
//vectorそのものに 新しいvectorを代入しようとした所 operatorで定義されてないらしくエラー(こっちは微妙>

//ちなみに 参照返しの返り値は 参照型で受け取らないと　コピーされるから速くならないっぽい
#include <vector>
#include <iostream>
using namespace std;

class Hoge
{
public:
  vector<int> vec;

  const vector<int>& getVec()
  {
    return vec;
  }

  vector<int>* getVec2()
  {
    return &vec;
  }

  Hoge(){
    for(int i=0; i<10; i++)
      vec.push_back(i);
  }
};

int main()
{
  Hoge h;
//  const vector<int> &v = h.getVec();
  //v[0] = 10;
  vector<int> u;
//  v = vector<int>();
  cout << h.getVec()[0] << endl;
  
  vector<int> *v2 = h.getVec2();
  (*v2)[0] = 20;
  cout << h.getVec()[0] << endl;

  v2->clear();
  for(auto it=v2->begin(); it!=v2->end(); it++)
  {
    cout << *it << endl;
  }
  return 0;
}
