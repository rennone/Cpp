#include<iostream>
#include<map>
using namespace std;
int n,k;
int fair[102][102];
map<int, map<int,int>> fair;
int cost[102];
int prev[102];
bool checked[102];
int st,gl;
const int NN=-1; //無限大

int myMin(int a, int b){
  if(a < 0) return b;
  if(b < 0) return a;
  return min(a,b);
}

void dksr(int now){
  checked[now]=true;
  map<int,int>::iterator it;
  for(it = fiar[now].begin(); it!=fiar[now].end(); it++){
    cost[
  }
}
int main(){
  while(cin>>n>>k,n|k){
    int a,b,c,d;
    for(int i=0;i<=k;i++){
      cin>>a;
      if(a==0){
	cin>>st>>gl;
      }
      else{
	cin>>b>>c>>d;
	fair[b][c]=fair[c][b]=d;
      }
    }
    for(int i=0; i<=n; i++){
      cost[i] = NN;
      checked[i] = false;
    }
    cost[st] = 0;
    dksr(st);

  }
}
