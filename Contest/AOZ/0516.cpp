#include<iostream>
#include<math.h>
using namespace std;
int n,k;
int a[100001];
int ans;
int main(){
  while(cin >> n >> k, n|k){
    ans = 0;
    int sum=0;
    for(int i=0; i<n;i++)
      a[i] = 0;
    
    for(int i=0; i<n;i++){
      cin >> a[i];
      if(i<k) {
	sum+=a[i];
      }
      else{
	sum = sum - a[i-k] + a[i]; 
	ans = max(ans, sum);
      }
    }
    cout << max(ans,sum) << endl;
  }

}
