/*
  8マスすごろく
  8マスの双六があり, n回目にゴールできる確率を求める.
  一番最初は0番がスタートであり,一回目は1-6マスに行く確率がそれぞれ1/6となる.
  ぴったりでないと止まれないため, 7マスにいるときに3がでると,つぎのマスは6のマスとなる.
  n回目でゴールできる確率を求める.
 */

#include <iostream>
#include <assert.h>
using namespace std;

//プログラムによる解法
unsigned long long ans1(int n)
{
  int k=n;
  long long p[9] = {0};
  p[0] = 1; //最初は0番にいる確率100%
  while(k--)
  {
    int t[9]={0};
    for(int i=0; i<9; i++)
      //今の位置から行ける場所に自信の確率を足す
      for(int j=1; j<=6; j++)
      {
        int l = (i+j) > 8 ? 16 - (i+j) : i+j; //通り過ぎたら折り返す
        t[l] += p[i];
      }

    //時間を進める.
    for(int i=0; i<9; i++)
      p[i] = t[i];
  }
  return p[8]; // * 6^{-n}
}

#include <cmath>
//一般形による解法
unsigned long long ans2(int n)
{
  //2回は降らないと到達できない.
  if(n<2)
    return 0;
  
  //プログラムのやり方で, それぞれの確率を求めていくと p_2マス(n) + p_8マス(n) = 6^(n-1), p_2マス(n) = p_8マス(n-1)とわかる
  //p(n) = 6^(n-1) - p(n-1) から求める.
  //p(n) = 6^(n-1) - 6^(n-2) + p(n-2) = 5*6^(n-2) + p(n-2)  
  if(n%2 == 0)
    return (pow(6, n)-1)/7; 
  else
    return (pow(6, n)-6)/7 + 1;
}

int main()  
{
  for(int i=0; i<13; i++)
  {
    if( ans1(i) != ans2(i) )
    {
      cout << i << endl;
      cout << ans1(i) << "," << ans2(i) << endl;
      break;
    }
    assert(ans1(i) == ans2(i));
  }
  cout << "OK" << endl;
}
