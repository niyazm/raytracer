#ifndef _VEC3_H_
#define _VEC3_H_

#include <iostream>
#include <iomanip>
#include <cmath>

class Vec3f
{
public:
  //Constructors
  Vec3f();

  Vec3f(float _x, float _y, float _z);

  Vec3f(const Vec3f* V);

  float& operator[](unsigned int i);

  //Assignment operators and boolean operators
  Vec3f operator=(const Vec3f& rhs);

  Vec3f operator=(const float x);

  Vec3f operator=(const Vec3f* rhs);

  bool operator==(const Vec3f& rhs);

  bool operator!=(const Vec3f& rhs);

  //Arithmetic assignment operators
  Vec3f& operator+=(const Vec3f& rhs);

  Vec3f& operator-=(const Vec3f& rhs);

  Vec3f& operator*=(const float& rhs);

  Vec3f& operator*=(const Vec3f& rhs);

  Vec3f& operator/=(const float& rhs);

  //Basic Arithmetic operators
  Vec3f operator+(const Vec3f& rhs);

  Vec3f operator-();

  Vec3f operator-(const Vec3f& rhs);

  Vec3f operator*(const float& x);

  Vec3f operator*(const Vec3f& rhs);

  Vec3f operator/(const float& rhs);

  //Dot products, Vector math stuff
  //float dot(const Vec3f& rhs);

  float dot(Vec3f& rhs);

  float squaredMagnitude();

  float magnitude();

  void normalize();

  friend std::ostream& operator<<(std::ostream& os, const Vec3f& V);

protected:
  float components[3];
};



#endif
