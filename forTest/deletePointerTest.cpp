#include <iostream>
#include <memory>
#include <vector>
using namespace std;

/*
スマートポインタのdeleteされるタイミングをテスト
 */
class Hoge
{  
public:
  static int id;
  int a;
  Hoge()
  {
    a = id++;
  }
  ~Hoge()
  {
    cout << "delete Hoge" << endl;
  }
  void print()
  {
    cout << a << endl;
  }
};

int Hoge::id = 0;

class HaveHoge
{
  shared_ptr<Hoge> hoge_ptr;
public:
  HaveHoge()
  {
    hoge_ptr = make_shared<Hoge>();
  }

  shared_ptr<Hoge> getHoge()
  {
    return hoge_ptr;
  }
};

void vecShared(vector<shared_ptr<Hoge>> &vec)
{
  vec.erase(remove_if(vec.begin(),
		      vec.end(),
		      [](shared_ptr<Hoge> x){return x->a%2 == 0;}
		      )
	    , vec.end());

  cout << "vector deleted" << endl;

    
}

int main()
{
  vector<shared_ptr<Hoge>> share_list;
  for(int i=0; i<10; i++)
    {
      share_list.push_back(make_shared<Hoge>());
    }

  auto v = share_list[2];
  vecShared(share_list);

  cout << "end" << endl;

  Hoge *h = new Hoge();
    printf("%p", h);
  delete h;

  printf("%p", h);
  return 0;
}
