#include<iostream>
#include<algorithm>
using namespace std;
int n,k;
int a[100001];
int ans;
int white;


void myCount(){
  ans = 0;
  int l=1;
  for(int i=1; i<k; i++){
    if(a[i] == a[i-1]+1)
      l++;
    else
      l = 1;
    ans = max(ans,l);
  }
}

void whiteCount(){
  bool flag = false;
  int l = 1;
  int prev;
  ans = 0;
  for(int i=1; i<k; i++){
    if(a[i] == a[i-1]+1){
      l++;
    }
    else if(a[i] == a[i-1]+2){
      if(!flag){
	flag = true;
	l+=2;
	prev = l-1;
      }
      else{
	l = l-prev;
	l+=2;
	prev = l-1;
      }
    }
    else{
      l = 1;
      flag = false;
    }
    ans = max(ans,l);
  }
  
}



int main(){
  while(cin >> n >> k, n|k){
    int tmp;
    white = 0;
    for(int i=0; i<k; i++){
      cin >> tmp;
      if(tmp==0){
	white = 1;
	a[i] = -5;
      }
      else
	a[i] = tmp;
    }
    sort(a,a+k);
    if(white)
      whiteCount();
    else
      myCount();

    cout << ans << endl;
  }
}
