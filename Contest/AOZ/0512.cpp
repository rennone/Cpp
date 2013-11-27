#include<iostream>
char str[1001];
using namespace std;

int main(){
  string tmp;
  int i=0;

  getline(cin, tmp);
  for(int i=0; i<tmp.size(); i++){
    cout << (char)( (tmp[i] - 'A' + 23)%26 + 'A') ;    
  }
  cout << endl;
  return 0;
}
