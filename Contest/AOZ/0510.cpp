#include<iostream>
#include<math.h>
using namespace std;
int A;
int B;
int ans;
int main(){
  ans = 0;
  A = B = 0;
  int tmp;
  for(int i=0; i<4;i++){
    cin >> tmp;
    A+=tmp;
  }
  
  for(int i=0; i<4; i++){
    cin >> tmp;
    B+=tmp;
  }
  cout << max(A,B) << endl;
    
}
