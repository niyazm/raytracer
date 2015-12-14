#ifndef __HIT__
#define __HIT__

#include "Vec3.hpp"
//#include "Material.hpp"

class Hit{
public:
  double t;
  Vec3f normal;
  Vec3f ray;
  //Material* mat;
  int mat;
  Vec3f point;
	Vec3f view;
  Hit();
  Hit(double _t, Vec3f _p, Vec3f _n, Vec3f _r, int _m);
  Hit(const Hit& h);
  //String print();
  //Hit& operator=(Hit& h);
protected:
};

#endif
