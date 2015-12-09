#include <iostream>
#include "Vec3.hpp"
using namespace std;

int main()
{
  Vec3f a, b, c, d, e;
  cout << a << b << c << d << e << endl;
  a = Vec3f(1,0,0);
  b = Vec3f(0,1,0);
  c = Vec3f(0,0,1);
  a += b += c;
  cout << a << endl;
  a *= 4;
  cout << a << endl;
  a /= 4;
  cout << a << endl;
  a -= b -= c;
  d = e = a;
  cout << d << endl;
  a = Vec3f(1,0,0);
  b = Vec3f(0,1,0);
  c = Vec3f(0,0,1);
  cout << (c == (a *= b)) << endl; 
  return 0;
}
