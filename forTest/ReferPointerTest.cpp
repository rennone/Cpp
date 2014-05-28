#include <iostream>
using namespace std;

void print2nd(int &a)
{
  int *p = &a;
  for( int i=0; i< 10; i++)
    *(p+i) += 1;
}

void movePtr(int* &a)
{
  a+=5;
  cout << *a << endl;
}

int main()
{
  int A[] = {1,2,3,4,5,6,7,8,9,0};
  int* &B = A;  //これは Aが配列だから無理 -> Aそのもののポインタを進めれたら, A[0] でもとのA[5]を指すような事になっちゃうから禁止されてる？
  movePtr(B);
  cout << *A << endl;

  return 0;
}
