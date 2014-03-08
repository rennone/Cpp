#include <iostream>
using namespace std;

int main()
{
  int x[] = {1,2,3,4 };

  for(auto a : x)
  {
    a = 0;    
  }

  for(auto a : x)
  {
    cout << a << endl;    
  }
  
  return 0;  
}
