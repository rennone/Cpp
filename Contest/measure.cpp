#include<iostream>
#include<cstring>
#include<sys/time.h>
using namespace std;
const int NUM = 1000000;
int measures[NUM+1];

//公約数を数えるアルゴリズム
void count1()
{
  memset(measures,0, sizeof(measures));
  for(int i=1; i<=NUM; i++)
  {
    for(int j=i; j<NUM; j+=i)
    {
      measures[j]++;
    }
  }
}

//??
void count2()
{
  memset(measures,0, sizeof(measures));
  for(int i=1; i<=NUM; i++){
    for(int j=i; j>=1; j--){
      if(j&i == 0)
	measures[j]++;
    }
  }
}

int main(){
  struct timeval t0, t1;
  struct timeval t2, t3;

  gettimeofday(&t0, NULL);
  count1();
  gettimeofday(&t1, NULL);
  cout << (t1.tv_sec - t0.tv_sec) + 0.000001*(t1.tv_usec - t0.tv_usec) << endl;

  gettimeofday(&t0, NULL);
  count2();
  gettimeofday(&t1, NULL);
  cout << (t1.tv_sec - t0.tv_sec) + 0.000001*(t1.tv_usec - t0.tv_usec) << endl;
  
}
