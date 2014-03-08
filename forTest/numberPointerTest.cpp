#include <stdio.h>

class Hoge
{
public:
  int a;
  Hoge()
  {
    a = 0;
  }
  void hoge(const float &rhs)
  {
    a = rhs;
    printf("a=%p, rhs=%p \n", &a, &rhs);
  }  
};


int main()
{

  Hoge h;

  {
    int a=5;
    h.hoge(a);
  }

  printf("\n %d \n\n", h.a);
  return 0;
}
