#include<iostream>
using namespace std;
bool submit[31]={0};
int main(){
  int tmp;
  for(int i=0; i<28;i++){
    cin >> tmp;
    submit[tmp-1] = true;
  }
  for(int i=0;i<30;i++){
    if(submit[i]) continue;
    cout << i+1 << endl;
  }
}
