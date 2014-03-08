#include <iostream>
using namespace std;

class Vector2
{
public:
  float x, y;
  Vector2()
  {
    x = y = 0;
  }
  Vector2& set(const float &x, const float &y)
  {
    this->x = x;
    this->y = y;
    return *this;
  }
  
  Vector2& add(const float &x, const float &y)
  {
    this->x += x;
    this->y += y;
    return *this;
  }
};

int main()
{
  Vector2 vec;
  float x=10, y=20;
  vec.set(x,y);
  cout << vec.x << " " << vec.y << endl;

  x = 5; y = 30;
  cout << vec.x << " " << vec.y << endl;

  Vector2 &vec2 = vec.add(x,y).add(x,y);
  cout << vec.x << " " << vec.y << endl;
  vec2.set(100, 200);
  cout << vec.x << " " << vec.y << endl;
  return 0;
}

