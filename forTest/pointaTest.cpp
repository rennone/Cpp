#include <iostream>
using namespace std;
int main()
{
  int **p;
  p = new int*[10];

  for(int i=0; i<10; i++)
  {
    p[i] = new int[10];
  }

  for(int i=0; i<10; i++)
  {
    for(int j=0; j<10; j++)
    {
      p[i][j] = i*10+j;
    }
  }

  for(int i=0; i<10; i++)
  {
    for(int j=0; j<10; j++)
    {      
      cout << p[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
