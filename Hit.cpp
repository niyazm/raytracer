#include "Hit.hpp"
#include <string>

Hit::Hit(){
  t = 10000.0f;
  point = Vec3f();
  normal = Vec3f();
  mat = 0;
  view = Vec3f();
}

Hit::Hit(double _t, Vec3f _p, Vec3f _n, Vec3f _r, int _m){
  t = _t;
  point = _p;
  normal = _n;
  normal.normalize();
  mat = _m;
  view = _r;
  view.normalize();
}

Hit::Hit(const Hit& h){
  t = h.t;
  point = h.point;
  normal = h.normal;
  mat = h.mat;
  view = h.view;
}
