
#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;

#define MAX_N 1000
int N, L[MAX_N];

ll solve()
{
  ll ans = 0;
  priority_queue<int, vector<int>, greater<int> > que;

  for(int i=0; i<N; i++)
  {
    que.push(L[i]);
  }

  while( que.size() > 1)
  {
    int l1, l2;
    l1 = que.top();
    que.pop();
    l2 = que.top();
    que.pop();

    ans += l1+l2;
    que.push(l1+l2);
  }

  return ans;
}

//大きい板から順に切り出す方法. うまくいかない
// 1,2..10に切り出すときに
// 55 => 10 45 とするよりも
// 55 => 22 33 として, 切り出していった方が効率がいい.
ll solve2()
{
  ll ans = 0;
  priority_queue<int> que;

  ll length = 0;
  for(int i=0; i<N; i++)
  {
    que.push(L[i]);
    length += L[i];
  }

  while( que.size() > 1)
  {
    ans += length;
    ll l = que.top();
    que.pop();
    length -= l;    
  }

  return ans;
}

int main()
{
  /*
  for(int i=0; i<10; i++)
  {
    N = rand()%10;
    for(int i=0; i<N; i++)
    {
      L[i] = rand()%10;
    }

    ll ans1 = solve();
    ll ans2 = solve2();
    if( ans1 != ans2)
    {
      cout << ans1 << "," << ans2 << endl;
    }
  }
  */
  N = 10;
  for(int i=0; i<N; i++)
    L[i] = i+1;
  cout << solve() << " " << solve2() << endl;
}

/*
  1 ~ 10の板に切り出す例
          55
         22 33
       15 18 22
     10 12 15 18
     7 8 9 9 12 10
   6   6  7 8 9 9 10
   6  4 5 6 7 8 9 10
 3  3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 9 10
*/
