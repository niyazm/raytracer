#ifndef __HIT__
#define __HIT__

#include "Vec3.hpp"
#include "Hit.hpp"
#include "Material.hpp"

class Hit{
public:
  double t;
  Vec3f normal;
  Vec3f ray;
  Material* mat;
  Hit();
  Hit(double _t, Vec3f _n, Vec3f _r, Material* _m);
  Hit(const Hit& h);
  //Hit& operator=(Hit& h);
protected:
};

#endif
