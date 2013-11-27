#include<iostream>
#include<math.h>
using namespace std;
int n,m;

//Aにカップを集める, numは残りコップの数
int gatA(int A, int B, int C, int num){
  if(num==0) return 0; //どのポールにもカップが無い

  if(A & 1)
    return gatA(A >> 1, B >> 1, C >> 1, num-1);                  //1番小さいコップがAにある(そのまま,カップの数を減らした問題と同じ)
  else if(B & 1)
    return pow(3, num-1) + gatA(C >> 1, B >> 1, A >> 1, num-1);  //Bにある(2番目以上のカップをCにあつめて,１をずらして,その上に2番目以上のカップをのせる)
  else
    return 2*pow(3,num-1) + gatA(A >> 1, B >> 1, C >> 1, num-1); //Cにある(2番目以上のカップをAにあつめて, 1をずらして,その上に2番目以上のカップをのせる)
}

int main(){
  while(cin >> n >> m, n||m){
    int cup[3] = {0};
    for(int i=0; i<3; i++){
      int k, t;
      cin >> k;
      for(int j=0; j<k;j++){
	cin >> t;
	cup[i] |= 1 << (t-1);
      }
    }
    
    int ans = min(gatA(cup[0], cup[1], cup[2], n), gatA(cup[2], cup[1], cup[0], n));
    if(m < ans) ans = -1;
    cout << ans << endl;
  }
}
