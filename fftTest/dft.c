#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include<complex.h>
typedef double complex Complex;

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

Complex* cdft(Complex data[], int n)
{
  Complex *res = (Complex*) malloc(sizeof(Complex)*n);
  
  Complex arg = I*2*M_PI/n;
  for(int i=0; i<n; i++)
  {
    res[i] = 0;
    for(int j=0; j<n; j++)
    {
       res[i] += data[j] * cexp(arg*j*i);
    }
  }
  return res;
}


#define n 1<<13
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
  
  Complex *res = cdft(datas, n);
  
  FILE *fp = fopen("rest2.txt", "w");
  for(int i=0; i<1500; i++)
  {
    fprintf(fp, "%lf\n", cabs(res[i]) / sqrt(n));
  }

free(res);
  fclose(fp);  
  printf("finish\n");
  return 0;
}

