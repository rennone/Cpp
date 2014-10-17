#include<stdlib.h>
#include<stdio.h>
int main()
{
  for(int i=0; i<5; i++)
  {
    srand(0);
    for(int j=0; j<10; j++)
    {
      printf("%d ",rand()%20);
    }
    printf("\n");
  }
}
