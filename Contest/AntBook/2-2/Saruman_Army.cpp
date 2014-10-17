#include<iostream>
using namespace std;
const int MAX_N = 1005;

int main(){
  int N = 6;
  int R = 10; 
  int X[MAX_N] = {1,7,15,20,30,50};
  int a = 0;
  int num = 0;
  int l = X[0]-R-1;
  int i=0;
  while(i < N){
    a = X[i++];
    while(X[i]-a<=R) i++;
    a = X[i-1];
    while(X[i]-a<=R) i++;
    num++;
  }
  cout << num << endl;
}
