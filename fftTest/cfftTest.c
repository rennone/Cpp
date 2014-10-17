#include "cfft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int n = 1 << 13;

Complex *data[360];

double gauss(double t)
{
  return 0;
}

#define C_S 0.70741
#define H_U 10

//波長 -> インデックス変換
int toIndex(int lambda)
{
  return floor(C_S * H_U * n / lambda + 0.5); //四捨五入
}

void debug(Complex *c, FILE *fp)
{
  for(int i=0; i<360; i++)
  {
    fprintf(fp, "%lf\n", cabs(c[i]));
  }
}

double c_abs(double re, double im)
{
  return sqrt(pow(re, 2) + pow(im, 2));
}

int main()
{
  FILE *fp_r = fopen("Eth_r.txt", "r");
  FILE *fp_i = fopen("Eth_i.txt", "r");

  Complex datas[n];

  memset(datas, 0, sizeof(Complex)*n);
  for(int j=0; j<1500; j++)
  {
    double rm, im;
    fscanf(fp_r, "%lf", &rm);
    fscanf(fp_i, "%lf", &im);
    datas[j]   = rm + I*im;
  }
  
  printf("read file\n");

  FILE *outR = fopen("re.txt", "w");
  FILE *outI = fopen("im.txt", "w");
  for(int i=0; i<1500; i++){
    fprintf(outR, "%lf\n", creal(datas[i]));
    fprintf(outI, "%lf\n", cimag(datas[i]));
  }
  fclose(outR);
  fclose(outI);
  
  fft1x(datas, n, 0, 0);
  
  FILE *fp = fopen("rest2.txt", "w");
  for(int i=0; i<1500; i++)
  {
    fprintf(fp, "%lf\n", cabs(datas[i]) / sqrt(n));
  }
  
  fclose(fp);  
  printf("finish\n");
  return 0;
}
