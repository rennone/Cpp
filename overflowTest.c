#include <stdio.h>


int main()
{
  int p = 0x80000000  - 0xF;
  for(int i=0; i<0x10; i++)
  {
     printf("%d\n", p++);
  }

}
