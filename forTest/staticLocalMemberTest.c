#include<stdio.h>

//関数内static変数の初期化に関するテスト

int* privateStaticMember()
{
  static int i = 100;
  printf("i=%d\n",i);
  return &i;
}

int* publicStaticMember()
{
  //error pricateStaticMember()がコンパイル時定数ではないので初期化できない.
  static int *i = privateStaticMember();
  return i;
}

int main()
{
  for(int i=0; i<10; i++)
  {
    int *j = publicStaticMember();
  }
}
