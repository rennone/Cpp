#include <stdio.h>

typedef struct FieldInfo
{
  int a, b, c;
}FieldInfo;


int main()
{
  FieldInfo f, *fp;
  f.a = 0; f.b = 1; f.c = 2;

  int *arr = (int*)&f;

  for(int i=0; i<sizeof(FieldInfo)/sizeof(int); i++)
  {
    printf("%d ", arr[i]);
  }

  int arr2[6] = {4,5,6};
  fp = (FieldInfo*)arr2;

  FieldInfo g = *fp;
  printf("\n%d %d %d\n", g.a, g.b, g.c);
}
