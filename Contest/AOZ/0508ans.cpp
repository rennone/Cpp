#include<iostream>
#include<math.h>
#include<stack>
#include<vector>
using namespace std;
int n;
int ans;
vector<int> rope[101];
bool searched[101], tmpSearched[101];

int from[101];

int dfs(int prev, int depth){
  for(int i=0; i<rope[prev].size(); i++){
    if(tmpSearched[rope[prev][i]]) continue;
    tmpSearched[rope[prev][i]] = true;
    if(rope[prev].size() > 2) searched[prev] = true;
    ans = max(ans, dfs(rope[prev][i],depth+1));
    tmpSearched[rope[prev][i]] = false;;
  }
  return depth;
  
}

int main(){
  while(cin >> n, n){
    ans = 0;
    for(int i=0; i<101; i++) searched[i] = false;
    
    for(int i=0; i<101;i++)
      rope[i].clear();

    int a,b;
    for(int i=0; i<n; i++){
      cin >> a >> b;
      rope[a].push_back(b);
      rope[b].push_back(a);
    }
    
    for(int i=0; i<n; i++){
      if(!searched[i])
	dfs(i, 0);
    }
    cout << ans << endl;
  }

}
