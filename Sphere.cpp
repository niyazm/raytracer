#include "Sphere.hpp"

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

Hit Sphere::hit(const Ray& ray){
  double t;
  Vec3f o = ray.o;
  Vec3f d = ray.d;
  Vec3f temp = o - center;
  double a, b, c;
  a = d.dot(d);
  b = (temp.dot(d)) * 2.0;
  c = temp.dot(temp) - radius * radius;
  double discriminant;
  discriminant = b * b - 4.0 * a * c;

  if (discriminant < 0.0) return Hit();

  double e = sqrt(discriminant);
  double denominator = a * 2.0;
  t = (-b - e) / denominator;
  if (t > .0001){
    Vec3f norm = (temp + (d * t)) / radius;
		Vec3f view = d;
		view.normalize();
		view *= -1;
    return Hit(t, norm, view, mat);
  }
  t = (-b + e) / denominator;
  if (t > .0001){
    Vec3f norm = (temp + (d * t)) / radius;
		Vec3f view = d;
		view.normalize();
		view *= -1;
    return Hit(t, norm, view, mat);
  }
  return Hit();
}


