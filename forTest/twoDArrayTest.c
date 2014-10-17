//1ラメラの式
typedef struct Lamela
{
  double a, b1, b2; //傾き, 下の切片, 上の切片
  int id; //ラメラのid
} Lamela;

#define NUM 10
static Lamela lamelas[2][NUM];

#include <stdio.h>

int main()
{
  for(int i=0; i<NUM; i++)
  {
    for(int j=0; j<2; j++)
    {
      lamelas[j][i].a  = j*NUM*NUM + NUM*i;
      lamelas[j][i].b1 = j*NUM*NUM + NUM*i+1;
      lamelas[j][i].b2 = j*NUM*NUM + NUM*i+2;
    }
  }

  Lamela *lam = &lamelas[0][0];
  printf("%lf %lf %lf \n", lam->a, lam->b1, lam->b2);
  printf("%lf %lf %lf \n", lamelas[0][0].a, lamelas[0][0].b1, lamelas[0][0].b2);
}
