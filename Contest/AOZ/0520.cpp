#include<iostream>
#include<cstring>
#include<map>
#include<cstdlib>
using namespace std;

class  info{
public:
  int p,q,r,b;
  info(int _a,int _b, int _c, int _d):p(_a), q(_b), r(_c), b(_d){  }
  info(){}
};

int n;
info bar[102];

int ans;
int parent[102];
 
int gcd(int a, int b) {
    if(a < b) return gcd(b, a);
    while(true) {
        int tmp = a % b;
        a = b;
        b = tmp;
        if(b == 0) break;
    }
    return a;
}

int lcm(int a, int b){ 
  return a*b/gcd(a,b);
}

int dfs(int i){
  int red  = (bar[i].r==0 ? 1:dfs(bar[i].r) );
  int blue = (bar[i].b==0 ? 1:dfs(bar[i].b) );
  int wr = red*bar[i].p;
  int wb = blue*bar[i].q;
  int gc = gcd(wr, wb);
  return red*(wb/gc) + blue*(wr/gc);
  //  return lc/bar[i].p + lc/bar[i].q;
}

int main(){
  while(cin>>n,n){
    memset(parent,0,sizeof(parent));
    
    int p,q,r,b;
    for(int i=1;i<=n;i++){
      cin >> p >> q >> r >> b;
      bar[i] = info(p, q, r, b);
      if(r != 0)  parent[r] = i;
      if(b != 0)  parent[b] = i;
    }

    int top = 1;
    while(parent[top] != 0){
      top = parent[top];
    }

    cout << dfs(top) << endl;
  }
}
