#include<iostream>
using namespace std;
int a,b,c;
int num;
int S[2][302]; //0:故障, 1:正常, 2:不確か
int SS[302];
int L[1001], M[1001],N[1001],R[1001];
bool now;
int main(){
  while(cin>>a>>b>>c, a|b|c){
    for(int i=1; i<=a+b+c;i++)
      S[0][i] = S[1][i] = 2;
    cin >> num;
    for(int i=0; i<num; i++){
      cin >> L[i] >> M[i] >> N[i] >> R[i];
    }
    now = 0;
    bool flag = true;
    while(flag){
      now = !now;
      for(int i=0; i<num; i++){
	if(R[i]==1){
	  S[now][L[i]] = S[now][M[i]] = S[now][N[i]] = 1;
	}
	else{
	  if(S[!now][L[i]] == 1 && S[!now][M[i]] == 1)
	    S[now][N[i]] = 0;
	  if(S[!now][L[i]] == 1 && S[!now][N[i]] == 1)
	    S[now][M[i]] = 0;
	  if(S[!now][N[i]] == 1 && S[!now][M[i]] == 1)
	    S[now][L[i]] = 0;
	}
      }
      flag = false;
      for(int i=1; i<=a+b+c; i++)
	flag = flag || !(S[now][i] == S[!now][i]);
    }
    for(int i=1; i<=a+b+c; i++)
      cout << S[now][i] << endl;
  }
}

  
