#define MAX_N 1000
int par[MAX_N];  //親番号 par[x] = x のときxは根
int rank[MAX_N]; //木のランク

//n要素で初期化
void init(int n)
{
  for(int i=0; i<n; i++)
  {
    par[i] = i;
    rank[i] = 0;
  }
}

//木の根を求める
int find(int x)
{
  if( par[x] == x)
    return x;
  else
    return par[x] = find(par[x]);  //親をたどって再起的に探し,最後に根に直接つなぐ
}

//xとyの属する木を併合
void unite(int x, int y)
{
  x = find(x);
  y = find(y);
  if( x == y )
    return;

  if(rank[x] < rank[y])
  {
    par[x] = y;
  }
  else
  {
    par[y] = x;
    if(rank[x] == rank[y])
      rank[x]++;
  }      
}

//同じグループか否か
bool same(int x, int y)
{
  return find(x) == find(y);
}

#include <iostream>
using namespace std;

//食物連鎖問題
#define MAX_K 100000
int N, K;
int T[MAX_K], X[MAX_K], Y[MAX_K];

void solve()
{  
  init(3*N); //i-A = i, i-B = i+N, i-C = i+2Nと表す.
  int ans = 0;
  for(int i=0; i<K; i++)
  {
    int t = T[i];
    int x = X[i];
    int y = Y[i];
    if( x < 0 || N <= x || y < 0 || N <= y)
    {
      ans++;
      continue;
    }

    // xはyと同じ種類という情報
    if( t==1 )
    {
      // すでに違うxとyが違う種類で併合されているときは矛盾した情報
      if( same( x, y+N) || same(x, y+2*N) || same(x+N, y) || same(x+N, y+2*N) ||same(x+2*N, y) ||  same(x+2*N, y+N))
      {
        ans++;
        continue;
      }
      else
      {
        //同じ種類と併合
        unite(x, y);
        unite(x+N, y+N);
        unite(x+2*N, y+2*N);
      }
    }
    // xはyを食べるという情報
    else
    {
      if( same(x, y) || same(x, y+2*N) || same(x+N, y+N) || same(x+N, y) || same(x+2*N, y+2*N) || same(x+2*N, y+N) )
      {
        ans++;
        continue;
      }
      else
      {
        unite(x, y+N);
        unite(x+N, y+2*N);
        unite(x+2*N, y);
      }
    }
  }

  cout << ans << endl;
}


int main()
{
  N = 100; K = 7;
  T[0] = 1; X[0] = 101; Y[0] = 1;
  T[1] = 2; X[1] = 1; Y[1] = 2;
  T[2] = 2; X[2] = 2; Y[2] = 3;
  T[3] = 2; X[3] = 3; Y[3] = 3;
  T[4] = 1; X[4] = 1; Y[4] = 3;
  T[5] = 2; X[5] = 3; Y[5] = 1;
  T[6] = 1; X[6] = 5; Y[6] = 5;

  solve();
}
