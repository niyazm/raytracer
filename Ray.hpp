#ifndef __RAY__
#define __RAY__

#include "Vec3.hpp"

class Ray{
public:
  Vec3f o, d;
  Ray();
  Ray(Vec3f _d);
  Ray(Vec3f _d, Vec3f _o);
protected:
};

#endif
