#ifndef __RGBCOLOR__
#define __RGBCOLOR__
#include "Vec3.hpp"

class RGBColor{
public:
  float r, g, b;
  RGBColor();

  RGBColor(float _r, float _g, float _b);

  RGBColor(float _r);
  
  RGBColor(Vec3f v);

  RGBColor& operator=(const RGBColor& rhs);

  RGBColor& operator+=(const RGBColor& rhs);

  RGBColor operator+(const RGBColor& rhs);

  RGBColor& operator*=(const float& rhs);

  RGBColor& operator*=(const RGBColor& rhs);
 
  RGBColor operator*(const float& rhs);

  RGBColor operator*(const RGBColor& rhs);

  RGBColor& operator/=(const float& rhs);

  RGBColor operator/(const float& rhs);

  RGBColor& operator-=(const RGBColor& rhs);

  RGBColor operator-(const RGBColor& rhs);
  
  //need exponentiation method
  
protected:
};

RGBColor operator*(const float& lhs, const RGBColor& rhs);

#endif
