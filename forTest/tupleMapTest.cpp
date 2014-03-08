#include <tuple>
#include <map>
#include <iostream>

using namespace std;

struct Index
{
  int v, n, u;
};

bool operator<(const Index& a, const Index& b)
{
    return std::tie(a.v, a.n, a.u) < std::tie(b.v, b.n, b.u);
}

  
int main()
{
  map< Index, int> foo;
  tuple<int, int> key = make_tuple(0,1);
  foo[ {1,2,3} ] = 4;

  cout << foo.count({1,2,3}) << endl;
  map<tuple<string, string, string>, int> employees;

  return 0;
}
