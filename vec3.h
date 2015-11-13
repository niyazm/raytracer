#ifndef _VEC3_H_
#define _VEC3_H_

#include <iostream>
#include <iomanip>
#include <cmath>

#define EPSILON 1e-6

bool equal(float a, float b){
  return (a == b) || ((a - EPSILON) < b && (a + EPSILON) > b);
}

bool notEqual(float a, float b){
  return (a != b) && ((a - EPSILON) > b || (a + EPSILON) < b);
}

class Vec3f
{
public:
  Vec3f(float _x = 0, float _y = 0, float _z = 0){
    components[0] = _x;
    components[1] = _y;
    components[2] = _z;
  }

  float& operator[](unsigned int i)  {
    if(i > 2)
    {
      return components[i%3];
    }
    return components[i];
  }

  void operator=(const Vec3f& rhs){
    for(int i = 0; i < 3; i++){
      components[i] = rhs.components[i];
    }
  }

  void operator=(const float x){
    for(int i = 0; i < 3; i++){
      components[i] = x;
    }
  }

  /*void operator=(const *float float_array){
    //dangerous if someone tries to use an array shorter than 3 elements, but thats life.
    //entire operator overload is commented out for this reason
    for(int i = 0; i < 3; i++){
      components[i] = float_array[i];
    }
  }*/

  void operator=(const Vec3f* rhs){
    for(int i = 0; i < 3; i++){
      components[i] = rhs->components[i];
    }
  }

  Vec3f operator+(const Vec3f& rhs){
    Vec3f returnMe;
    for(int i = 0; i < 3; i++){
      returnMe[i] = (*this).components[i] + rhs.components[i];
    }
    return returnMe;
  }

  Vec3f operator-(){
    Vec3f returnMe;
    for(int i = 0; i < 3; i++){
      returnMe[i] = (*this).components[i] * -1.0f;
    }
    return returnMe;
  }

  Vec3f operator-(const Vec3f& rhs){
    Vec3f returnMe;
    returnMe[0] = components[0] - rhs.components[0];
    returnMe[1] = components[1] - rhs.components[1];
    returnMe[2] = components[2] - rhs.components[2];
    return returnMe;
  }

  Vec3f operator*(const float& x){
    Vec3f returnMe;
    returnMe[0] = components[0] * x;
    returnMe[1] = components[1] * x;
    returnMe[2] = components[2] * x;
    return returnMe;
  }

  Vec3f operator*(const Vec3f& rhs){ //decided to use cross product since return types are the same for both multiplications
    float i, j, k;
    i = components[1] * rhs.components[2] - components[2] * rhs.components[1];
    j = components[0] * rhs.components[2] - components[2] * rhs.components[0];
    k = components[0] * rhs.components[1] - components[1] * rhs.components[0];
    Vec3f returnMe(i, -j, k);
    return returnMe;
  }

  float dot(const Vec3f& rhs){
    float returnMe = 0.0f;
    for(int i = 0; i < 3; i++){
      returnMe += components[i] * rhs.components[i];
    }
    return returnMe;
  }

  Vec3f operator/(const float& rhs){
    if(rhs == 0) throw ("Division by zero.");
    Vec3f returnMe;
    float recip = 1/rhs;
    returnMe[0] = components[0] * recip;
    returnMe[1] = components[1] * recip;
    returnMe[2] = components[2] * recip;
    return returnMe;
  }

  Vec3f operator+=(const Vec3f& rhs){
    for(int i = 0; i < 3; i++){
      components[i] = components[i] + rhs.components[i];
    }
  }

  Vec3f operator-=(const Vec3f& rhs){
    for(int i = 0; i < 3; i++){
      components[i] = components[i] - rhs.components[i];
    }
  }

  Vec3f operator*=(const float& rhs){
    for(int i = 0; i < 3; i++){
      components[i] = components[i] * rhs;
    }
  }

  Vec3f operator*=(const Vec3f& rhs){
    float i, j, k;
    i = components[1] * rhs.components[2] - components[2] * rhs.components[1];
    j = components[0] * rhs.components[2] - components[2] * rhs.components[0];
    k = components[0] * rhs.components[1] - components[1] * rhs.components[0];
    components[0] = i;
    components[1] = -j;
    components[2] = k;
  }

  Vec3f operator/=(const float& rhs){
    if(rhs == 0) throw ("Division by zero.");
    float recip = 1/rhs;
    for(int i = 0; i < 3; i++){
      components[i] = components[i] * recip;
    }
  }

  bool operator==(const Vec3f& rhs){
    for(int i = 0; i < 3; i++){
      if(notEqual(components[i], rhs.components[i])) return false;
    }
    return true;
  }

  bool operator!=(const Vec3f& rhs){
    for(int i = 0; i < 3; i++){
      if(notEqual(components[i], rhs.components[i])) return true;
    }
    return false;
  }

  float squaredMagnitude(){
    float returnMe = 0;
    for(int i = 0; i < 3; i++){
      returnMe += components[i] * components[i];
    }
    return returnMe;
  }

  float magnitude(){
    return sqrt(squaredMagnitude());
  }

  friend std::ostream& operator<<(std::ostream& os, const Vec3f& V);


protected:
  float components[3];
};

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

#endif
