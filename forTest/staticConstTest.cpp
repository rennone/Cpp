/* static const に式を入れる事ができるか*/
#include <cmath>
#include <iostream>
using namespace std;
class Hoge
{
public:
  static constexpr float TO_RADIANS = 1.0f/180.0f*M_PI;
};


int main()
{
  cout << 360*Hoge::TO_RADIANS << endl;
  return 0;
}
