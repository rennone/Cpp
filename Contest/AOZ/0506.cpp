#include<iostream>
#include<string>
#include<sstream>
using namespace std;

int n;
string number;
string newnumber;
string s;

void calc(){
  char c = number[0];
  int k=1;
  ostringstream o;
  newnumber = "";
    
  for(int i=1; i<number.size(); i++){
    if(number[i] == c){
      k++;
    }
    else{
      ostringstream out;
      out << k << c; 
      newnumber = newnumber + out.str();
      c = number[i];
      k=1;
    }
  }
  ostringstream out;
  out << k << c;
  newnumber = newnumber + out.str();
  
    
}
int main(){
  while(cin >> n , n){
    cin >> number;
 
    for(int i=0; i<n; i++){
      calc();
      number = newnumber;
    }
    
    cout << number << endl;
  }
  return 0;
}
