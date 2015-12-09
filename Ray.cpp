#include "Ray.hpp"

Ray::Ray(Vec3f _d){
  Ray(_d, Vec3f());
}

Ray::Ray(Vec3f _d, Vec3f _o){
  o = _o;
  d = _d;
}

Ray::Ray(){
  Ray(Vec3f());
}


