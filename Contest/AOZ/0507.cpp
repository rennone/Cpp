#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int n;


void draw(string str, int left, int rest){
  ostringstream out;
  out << left;
  str = str + out.str();
  if(rest == 0)
    cout << str << endl;
  else
    str = str + " ";

  for(int i=rest; i>0; i--){
    if(left < i) continue;
    draw(str, i, rest-i);
  }

}

int main(){
  while(cin >> n, n){
    for(int i=0; i<n; i++){
      draw("", n-i, i);
    }
  }
  return 0;
}
