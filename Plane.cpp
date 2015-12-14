#include "Plane.hpp"

Plane::Plane(Vec3f _n, Vec3f _p){
  point = _p;
  normal = _n;
}

Plane::Plane(Vec3f _n, float _offset){
  normal = _n;
  normal.normalize();
  Vec3f O = Vec3f(0,0,0);
  O -= _n * _offset;
  point = O;
}

Plane::Plane(Vec3f _n, Vec3f _p, int _m){
  point = _p;
  normal = _n;
  mat = _m;
}

Plane::Plane(Vec3f _n){
  Plane(_n, Vec3f(0.0f, 0.0f, 0.0f));
}

Plane::Plane(){
  Plane(Vec3f(1.0f, 0.0f, 0.0f));
}

void Plane::report(){
  std::cout << "NORMAL : " << normal;
  std::cout << " POINT : " << point;
  std::cout << std::endl;
}

Hit Plane::hit(const Ray& ray) {
  Vec3f o = ray.o;
  Vec3f d = ray.d;
	Vec3f view = d;
	view.normalize();
  double t = (point - o).dot(normal) / (d.dot(normal));
  Vec3f p = o + d * t;
  if (t > .0001){
    return Hit(t, p, normal, view, mat);
  }
  return Hit();
}
