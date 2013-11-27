#include<iostream>
using namespace std;

int coin[6]={500,100,50,10,5,1};

int main(){
  int v;
  while(cin>>v, v){
    int sum=0;
    v = 1000-v;
    for(int i=0; i<6; i++){
      sum += v/coin[i];
      v = v%coin[i];
    }
    cout << sum << endl;

  }
}
