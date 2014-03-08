#include <vector>
#include <iostream>
using namespace std;
int main()
{
  vector<int> vec;

  vec.reserve(1000);
  vec.push_back(10);

  cout << vec.size() << endl;
}
