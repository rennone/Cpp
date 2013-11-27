#include<algorithm>
#include<iostream>
#include<stdlib.h>
using namespace std;
const int MAX_N = 20005;

template<class T> void swap(T &a, T &b){
  T tmp;
  tmp = a;
  a = b;
  b = tmp;
}

template<class T>void _qsort(T a[], int left, int right){
  int M = (left + right)/2;
  if(M ==left){
    if(a[left] > a[right]) swap(a[left],a[right]);
    return;
  }
  _qsort(a, left, M);
  _qsort(a, left, M+1);
  
  T tmp[right-left+1];
  while(left < right){
    if(a[left] > a[right]){
      tmp[]
      left++;
    }
    else{
      left++;
      right++;
    }
  }
}

template<class T> void qsort(T a[], int N){
  int left=
}
int main(){
  int N=3;
  int L[MAX_N] = {8,5,8};
  sort(L,N);
  int sum = 0;
  for(int i=0; i<N; i++)   sum += L[i];

  int cost=0;
  for(int i=0; i<N; i++){
    cost += sum;
    sum -= L[i];
  }
  cout << cost << endl;
  
}
