#include <stdio.h>
#include <stdlib.h>
int f(int z)
{
  if(z<=1)
    return 0;

  return (z-1)*(z-1);
}

int main()
{
  int n = 1000;
  double c = 0.5;
  double lu = 2.0, ls = 0.01;
  double x = 0.0001, y = 0.0;
  FILE *fp = fopen("data.txt", "w");
  for(int i=0; i<n; i++)
  {
    fprintf(fp, "%lf , %lf \n", x, y);
    double px = lu*x;
    double py = ls*y;
    double fac = c*f( + ls*y);
    x = lu*x - fac;
    y = ls*y + fac;
  }
}
