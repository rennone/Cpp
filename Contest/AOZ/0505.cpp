#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
int n,m;
int place[105] = {-1};

int main(){
  while(cin >> n >> m, n|m){
    for(int i=0; i<m; i++) place[i] = 999-i; //
    
    for(int i=0; i<n; i++){
      int p;
      for(int j=0; j<m; j++){
	cin >> p;
	place[j] += 1000*p;
      }
    }

    sort(place, place+m, greater<int>());

   
    for(int i=0; i<m; i++){
      int a = place[i] % 1000;
      cout << 1000-a << (i==m-1? "" : " ");
    }
    cout << endl;
  }
  return 0;
}
