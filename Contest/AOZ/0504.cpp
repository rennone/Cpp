#include<iostream>
using namespace std;
int n,k,m,r;

int main(){
  while(cin >> n >> k >> m >> r, n||k||m||r){
    double p[100100];
    int num = k*n; //残りカードの枚数
    
    for(int i=0; i<n; i++){
      card[i] = k;
      mountain[i] = k;
      p[i] = (i==0 ? 1:0);
    }
    /*
    while(num>0){
      for(int i=0; i<n; i++){
	Doublle Tmp_p=p[i], tmp_c=card[i], tmp_m=mountain[i];
	
      }
      num--;
    }
    */
    
  }
}
			
