#include "Plane.hpp"

Plane::Plane(Vec3f _n, Vec3f _p){
  point = _p;
  normal = _n;
}

Plane::Plane(Vec3f _n){
  Plane(_n, Vec3f(0.0f, 0.0f, 0.0f));
}

Plane::Plane(){
  Plane(Vec3f(1.0f, 0.0f, 0.0f));
}

Hit Plane::hit(const Ray& ray) {
  Vec3f o = ray.o;
  Vec3f d = ray.d;
  double t = (point - o).dot(normal) / (d.dot(normal));
  if (t > .0001){
    return Hit(t, normal, mat);
  }
  return Hit();
}
