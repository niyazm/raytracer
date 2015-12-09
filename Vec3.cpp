#ifndef __VEC3_H__
#include "Vec3.hpp"
#endif

Vec3f::Vec3f(){
  for (int i = 0; i < 3; i++) components[i] = 0.0f;
}

Vec3f::Vec3f(float _x , float _y, float _z){
  components[0] = _x;
  components[1] = _y;
  components[2] = _z;
}

Vec3f::Vec3f(const Vec3f* V){
  components[0] = V->components[0];
  components[1] = V->components[1];
  components[2] = V->components[2];
}

float& Vec3f::operator[](unsigned int i)  {
  if(i > 2)
  {
    return components[i%3];
  }
  return components[i];
}

Vec3f Vec3f::operator=(const Vec3f& rhs){
  for(int i = 0; i < 3; i++){
    (*this).components[i] = rhs.components[i];
  }
  return (*this);
}

Vec3f Vec3f::operator=(const float x){
  for(int i = 0; i < 3; i++){
    (*this).components[i] = x;
  }
  return (*this);
}

Vec3f Vec3f::operator=(const Vec3f* rhs){
  for(int i = 0; i < 3; i++){
    (*this).components[i] = rhs->components[i];
  }
  return (*this);
}

Vec3f Vec3f::operator+(const Vec3f& rhs){
  return (*this) += rhs;
}

Vec3f Vec3f::operator-(){
  return (*this) *= 1.0f;
}

Vec3f Vec3f::operator-(const Vec3f& rhs){
  return (*this) -= rhs;
}

Vec3f Vec3f::operator*(const float& x){
  return (*this) *= x;
}

Vec3f Vec3f::operator*(const Vec3f& rhs){ //decided to use cross product since return types are the same for both multiplications
  return (*this) *= rhs;
}

/*float Vec3f::dot(const Vec3f& rhs){
  float returnMe = 0.0f;
  for(int i = 0; i < 3; i++){
    returnMe += components[i] * rhs.components[i];
  }
  return returnMe;
}*/

float Vec3f::dot(Vec3f& rhs){
  float returnMe = 0.0f;
  for(int i = 0; i < 3; i++){
    returnMe += components[i] * rhs.components[i];
  }
  return returnMe;
}

Vec3f Vec3f::operator/(const float& rhs){
  return (*this) /= rhs;
}

Vec3f Vec3f::operator+=(const Vec3f& rhs){
  for(int i = 0; i < 3; i++){
    (*this).components[i] += rhs.components[i];
  }
  return (*this);
}

Vec3f Vec3f::operator-=(const Vec3f& rhs){
  for(int i = 0; i < 3; i++){
    (*this).components[i] -= rhs.components[i];
  }
  return (*this);
}

Vec3f Vec3f::operator*=(const float& rhs){
  for(int i = 0; i < 3; i++){
    (*this).components[i] *= rhs;
  }
  return (*this);
}

Vec3f Vec3f::operator*=(const Vec3f& rhs){
  float i, j, k;
  i = components[1] * rhs.components[2] - components[2] * rhs.components[1];
  j = components[0] * rhs.components[2] - components[2] * rhs.components[0];
  k = components[0] * rhs.components[1] - components[1] * rhs.components[0];
  (*this).components[0] = i;
  (*this).components[1] = -j;
  (*this).components[2] = k;
  return (*this);
}

Vec3f Vec3f::operator/=(const float& rhs){
  if(rhs == 0) throw ("Division by zero.");
  float recip = 1/rhs;
  for(int i = 0; i < 3; i++){
    (*this).components[i] = components[i] * recip;
  }
  return (*this);
}

const float EPSILON = 1e-6f;

bool notEqual(float a, float b){
  return (a != b) && ((a - EPSILON) > b || (a + EPSILON) < b);
}

bool Vec3f::operator==(const Vec3f& rhs){
  for(int i = 0; i < 3; i++){
    if(notEqual(components[i], rhs.components[i])) return false;
  }
  return true;
}

bool Vec3f::operator!=(const Vec3f& rhs){
  for(int i = 0; i < 3; i++){
    if(notEqual(components[i], rhs.components[i])) return true;
  }
  return false;
}

float Vec3f::squaredMagnitude(){
  float returnMe = 0;
  for(int i = 0; i < 3; i++){
    returnMe += components[i] * components[i];
  }
  return returnMe;
}

float Vec3f::magnitude(){
  return sqrt(squaredMagnitude());
}

void Vec3f::normalize(){
  //float length = magnitude();
  float inv_length = 1/magnitude();
  for(int i = 0; i < 3; i++){
    components[i]*=inv_length;
  }
}

std::ostream& operator<<(std::ostream& os, const Vec3f& V){
  os << "< ";
  for(int i = 0; i < 3; i++)
  {
    os << V.components[i];
    if(i < 2)
    {
      os << ", ";
    }
    else
    {
      os << " >";
    }
  }
  return os;
}
