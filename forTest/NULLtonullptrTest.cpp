#include <iostream>
using namespace std;

int main()
{
  int* a = NULL;
  int* b = nullptr;

  if(a == b)
    cout << "equal" << endl;
  else
    cout << "not equal" << endl;

  return 0;
}
