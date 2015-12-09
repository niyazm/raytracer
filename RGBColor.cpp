#include "RGBColor.hpp"

RGBColor::RGBColor(){
  r = g = b = 0.0f;
}

RGBColor::RGBColor(float _r, float _g, float _b){
  r = _r;
  g = _g;
  b = _b;
}

RGBColor::RGBColor(float _r){
  r = g = b = _r;
}

RGBColor::RGBColor(Vec3f v){
  r = v[0];
  g = v[1];
  b = v[2];
}

RGBColor& RGBColor::operator=(const RGBColor& rhs){
  r = rhs.r;
  g = rhs.g;
  b = rhs.b; 
  return (*this);
}

RGBColor& RGBColor::operator+=(const RGBColor& rhs){
  r += rhs.r;
  g += rhs.r;
  b += rhs.r;
  return (*this);
}

RGBColor RGBColor::operator+(const RGBColor& rhs){
  return (*this) += rhs;
}

RGBColor& RGBColor::operator*=(const float& rhs){
  r *= rhs;
  g *= rhs;
  b *= rhs;
  return (*this);
}

RGBColor& RGBColor::operator*=(const RGBColor& rhs){
  r *= rhs.r;
  g *= rhs.g;
  b *= rhs.b;
  return (*this);
}

RGBColor RGBColor::operator*(const float& rhs){
  return (*this) *= rhs;
}

RGBColor RGBColor::operator*(const RGBColor& rhs){
  return (*this) *= rhs;
}

RGBColor& RGBColor::operator/=(const float& rhs){
  r /= rhs;
  g /= rhs;
  b /= rhs;
  return (*this);
}

RGBColor RGBColor::operator/(const float& rhs){
  return (*this) /= rhs;
}

RGBColor& RGBColor::operator-=(const RGBColor& rhs){
  r -= rhs.r;
  g -= rhs.g;
  b -= rhs.b;
  return (*this);
}

RGBColor RGBColor::operator-(const RGBColor& rhs){
  return (*this) -= rhs;
}
