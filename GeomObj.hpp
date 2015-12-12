#ifndef __GEOMOBJ__
#define __GEOMOBJ__

#include "Vec3.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Hit.hpp"

class GeomObj{
public:
  virtual Hit hit(const Ray& ray) = 0;
  virtual void report() = 0;
  Material* mat;
protected:
};

#endif
