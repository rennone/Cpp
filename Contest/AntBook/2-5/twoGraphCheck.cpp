#include <vector>
#include <iostream>
using namespace std;
#define MAX_V 1000
vector<int> G[MAX_V];
int V; //頂点数
int color[MAX_V]; //各頂点の色 1: 黒 -1: 白 0:未着色

//vをcで塗る
bool dfs(int v, int c)
{
  //未着色なら塗る
  if( color[v] == 0 )
  {
    color[v] = c;
  }
  else
  {
    //既に塗られていたら, 同じ色かどうか判定して終わる.
    return color[v] == c;
  }

  bool res = true;
  
  for( int i=0; i < G[v].size(); i++ )
  {
    int child = G[v][i];
    res = res && dfs(child, -c); //隣は別の色で塗る
  }
  
  return res;
}

void solve()
{
  for(int i=0; i<V; i++){
    color[i] = 0;
  }
  
  for(int i=0; i<V; i++)
  {
    if( color[i] == 0)
    {
      //未着色なら黒で塗る
      if( !dfs(i, 1) )
      {
        cout << "No" << endl;
        return;
      }
    }
  }
  cout << "Yes" << endl;
}
int main()
{
  /*
  V = 3;
  G[0].push_back(1);   G[0].push_back(2);
  G[1].push_back(0);   G[1].push_back(2);
  G[2].push_back(0);   G[2].push_back(1);
  */
  
  V=4;
  G[0].push_back(1);   G[0].push_back(3);
  G[1].push_back(0);   G[1].push_back(2);
  G[2].push_back(1);   G[2].push_back(3);
  G[3].push_back(0);   G[3].push_back(2);
  
  solve();
}
