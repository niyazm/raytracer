#ifndef __GEOMOBJ__
#define __GEOMOBJ__

#include "ray.h"
#include "shaderec.h"
#include "vec3.h"
#include <cmath>

class GeometricObject{
public:
  virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
  virtual void print_object(int tabs) = 0;
protected:
  RGBColor color;
};

class Sphere{
public:
  Sphere(void){
    radius = 1;
    center = Vec3f(0.0f, 0.0f, 0.0f);
  }
  Sphere(const Vec3f c, const float r){
    center = c;
    radius = r;
  }

  virtual bool hit (const Ray& ray, double& tmin, ShadeRec& sr) const{
    double t;
    Vec3f temp = ray.o - center;
    double a = ray.d.dot(ray.d);
    double b = 2.0 * temp.dot(ray.d);
    double c = temp.dot(temp) - radius * radius;
    double disc = b*b - 4.0 * a * c;
    if(disc < 0.0){
      return false;
    }else{
      double e = sqrt(disc);
      double denom = 2.0 * a;
      t = (-b - e) / denom;
      //if(t > kEpsilon) {
      if(t > 0.001) //suffern uses this value
        tmin = t;
        sr.normal = (temp.dot(ray.d * t))/radius;
        sr.local_hit_point = ray.o + t * ray.d;
        return(true);
      }
    }
    return false;
  }

  virtual void print_object(int tabs){
    tabsting = "";
    for (int i = 0; i < tabs; i++){
      tabstring += "\t";
    }
    cout << tabstring << "SPHERE :" << endl;
    cout << tabstring << "\t" << "center:" << center << " radius:" << radius << endl;
  }

private:
  Vec3f center;
  float radius;
};

class Plane: public GeometricObject{
public:
  Plane(void){
    point = Vec3f(0.0f, 0.0f, 0.0f);
    normal = Vec3f(0.0f, 0.0f, 1.0f);
  }
  Plane(const Vec3f p, const Vec3f n){
    point = p;
    normal = n;
  }

  virtual bool hit (const Ray& ray, double& tmin, ShadeRec& sr) const{
    double t = (point - ray.o) * (normal / (ray.d.dot(normal)));
    //if(t < kEpsilon){
    if(t > 0.001) //suffern uses this value
      tmin = t;
      sr.normal = normal;
      sr.local_hit_point = ray.o + t * ray.d;
    }
    else{
      return false;
    }
  }

  virtual void print_object(int tabs){
    tabsting = "";
    for (int i = 0; i < tabs; i++){
      tabstring += "\t";
    }
    cout << tabstring << "PLANE :" << endl;
    cout << tabstring << "\t" << "pip:" << point << " normal:" << normal << endl;
  }

private:
  Vec3f point; //point through wich the plane passes
  Vec3f normal; //normal to the plane
  //static const double kEpsilon;
}

#endif
