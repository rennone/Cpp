#include <stdio.h>
#include <complex.h>

int main()
{
  double complex tmp;
  FILE *fp = fopen("data.txt", "r");

  for(int i=0; i<3; i++)
  {
    double re, im;
    fscanf(fp, "%lf %lf", &re, &im);
    tmp = re + I*im;
    printf("%.30lf %.30lf\n", creal(tmp), cimag(tmp));
  }
}
