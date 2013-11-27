#include<iostream>
using namespace std;
int a,b,n;
bool junction[42][42] = {0};
int ans;
void dfs(int _a, int _b){
  if(_a>a || _b>b || junction[_a][_b])
    return;
  if(a==_a && b==_b) {
    ans++;
    return;
  }
  dfs(_a+1,_b);
  dfs(_a,_b+1);
}
int main(){
  while(cin >> a >> b, a|b){
    for(int i=0;i<42;i++)
      for(int j=0; j<42; j++)
	junction[i][j] = false;

    cin >> n;
    int l,m;
    for(int i=0; i<n; i++){
      cin >> l >> m;
      junction[l][m] = true;
    }
    ans = 0;
    dfs(1,1);
    cout << ans << endl;
  }
	
}
