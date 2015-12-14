#ifndef __SPHERE__
#define __SPHERE__

#include "GeomObj.hpp"
#include "Hit.hpp"
#include <iostream>

class Sphere : public GeomObj{
public:
  Vec3f center;
  float radius;
  virtual Hit hit(const Ray& ray); 
  virtual void report();
  Sphere();
  Sphere(Vec3f _c, float _r, int _m);
  Sphere(Vec3f _c, float _r);
  Sphere(Vec3f _c);
protected:
};

#endif

