#include "Sphere.hpp"
#include <iostream>

Sphere::Sphere(){
  Sphere(Vec3f(), 1.0f);
}

Sphere::Sphere(Vec3f _c, float _r){
  center = _c;
  radius = _r;
}

Sphere::Sphere(Vec3f _c){
  Sphere(_c, 1.0f);
}

void Sphere::report(){
  std::cout << "CENTER : " << center;
  std::cout << "RADIUS : " << radius;
  std::cout << std::endl;
}

Hit Sphere::hit(const Ray& ray){
  Vec3f o, d;
  o = ray.o;
  d = ray.d;
  double a, b, c;
  Vec3f tm = o - center;
  tm = center - o;
  a = d.squaredMagnitude();
  b = 2 * (d.dot(tm));
  c = (o - center).squaredMagnitude() - (radius * radius);
  double discriminant = b * b - 4.0 * a * c;
  if (discriminant < 0.0) return Hit();
  double e = sqrt(discriminant);
  double t = -b - e;
  /*if(discriminant >= 0.0){
    std::cout << this << std::endl << "\t" 
    << "Origin" << o << std::endl << "\t"
    << "Direction" << d << std::endl << "\t"
    "\t sPHRE:" << std::endl <<
    "\t\t" << center << " " << radius << std::endl;
    std::cout << "a = " << a << std::endl << "b = " << b << std::endl << "c = " << c << std::endl;
    std::cout << "discriminant = "<< discriminant <<std::endl;
    std::cout << "sqrt(disc) = " << e << std::endl;
    std::cout << "t ==>>>> " << t << std::endl;
  }*/
  if (t > .0001) {
    Vec3f norm  = (tm + (d * t));
    Vec3f view = d;
    view.normalize();
    view*=-1;
    return Hit(t, norm, view, mat);
  }
  return Hit();
}


