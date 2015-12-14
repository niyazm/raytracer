#ifndef __PLANE__
#define __PLANE__

#include "GeomObj.hpp"
#include "Hit.hpp"
#include <iostream>

class Plane : public GeomObj{
public:
  Vec3f point;
  Vec3f normal;
  virtual Hit hit(const Ray& ray);
  virtual void report();
  Plane();
  Plane(Vec3f _n);
  Plane(Vec3f _n, Vec3f _p);
  Plane(Vec3f _n, float _offset);
  Plane(Vec3f _n, Vec3f _p, int _m);
protected:
};

#endif
