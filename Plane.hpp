#ifndef __PLANE__
#define __PLANE__

#include "GeomObj.hpp"

class Plane : public GeomObj{
public:
  Vec3f point;
  Vec3f normal;
  virtual Hit hit(const Ray& ray);
  Plane();
  Plane(Vec3f _n);
  Plane(Vec3f _n, Vec3f _p);
protected:
};

#endif
