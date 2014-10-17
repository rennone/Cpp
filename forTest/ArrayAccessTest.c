#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>
static struct timeval timer1, timer2;

//1次元配列でまとめてmallocした領域を, ポインタ配列を使って2次元配列のように扱う方法
// 動的に2次元配列を作るときに,領域をまとめて確保できるかと思いきや,
// ポインタ配列の方も動的に確保する必要があるため。アクセス速度の面でのメリットはなさそう
#define NX 10
#define NY 5
#define NZ 500
int main()
{
  int *data = (int*)malloc(sizeof(int)*NX*NY);
  
  for(int i=0; i<NX; i++)
    for(int j=0; j<NY; j++)
      data[i*NY+j] = i*NY+j;
  
  int **accessor = (int**)malloc(sizeof(int*)*NX);
  for(int i=0; i<NX; i++)
    accessor[i] = &data[i*NY];

  for(int i=0; i<NX; i++)
    for(int j=0; j<NY; j++)
      printf("%d\n",accessor[i][j]);
}
