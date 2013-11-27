#include<iostream>
#include<sys/time.h>
using namespace std;
int main(){
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);
  gettimeofday(&t2, NULL);
  cout << (t2.tv_sec-t1.tv_sec) + (t2.tv_usec-t1.tv_usec)*1e-6 << endl;
}
