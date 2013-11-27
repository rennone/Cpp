#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
bool now;
int card[2][201];

void riffle(){
  for(int i=0; i<n; i++){
    card[!now][2*i] = card[now][i];
    card[!now][2*i+1] = card[now][i+n];
  }
}

void cut(int k){
  for(int i=0; i<2*n-k;i++){
    card[!now][i] = card[now][i+k];
  }
  for(int i=0; i<k; i++){
    card[!now][i+2*n-k] = card[now][i];
  }
  
}

int main(){
  cin >> n >> m;
  now = 0;
  for(int i=0; i<2*n; i++)
    card[now][i] = i+1;

  int k;
  for(int j=0; j<m; j++){
    cin >> k;
    if(k==0)
      riffle();
    else
      cut(k);
    now = !now;
  }
  for(int i=0; i<2*n; i++)
    cout << card[now][i] << endl;
  return 0;
}
