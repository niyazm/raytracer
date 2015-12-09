//need the following objects:
//GeometricObject
//derive->plane, sphere
//Phong Material (no base material class)
//directional light, ambient light
//rgbcolor
//viewplane (is more of a data struct)
//shaderecord/hit object
//group to contain geo objs
//camera->able to change vp dist, builds in vp
//

#include "vec3.h"
#include <iostream>
#include <string>
#include <vector>

Ray::Ray(){
  o = Vec3f();
  d = Vec3f();
}

Ray::Ray(Vec3f _d){
  o = Vec3f();
  d = _d;
}

Ray::Ray(Vec3f _d, Vec3f _o){
  o = _o;
  d = _d;
}





class Hit{ //has minimum t value of hit, and normal of obj hit, pointer to obj hit, but maybe instead of a poitner is should just have the material
public:
protected:
};

class GeomObj{
public:
  virtual Hit hit(const Ray& ray, double& tmin) const = 0;
  virtual void print();
protected:
  Material* material;
};

class Sphere : public GeomObj{
public:
  virtual bool hit(const Ray& ray, double& tmin, Hit& hit) const {
    double t;
    Vec3f origin = ray.o;
    Vec3f direction = ray.d;
    Vec3f center_;
    Vec3f temp = origin - center_;
    Vec3f radius_;
    double a, b, c, discriminant;
    a = direction.dot(direction);
    b = temp.dot(direction) * 2.0;
    c = temp.dot(temp) -  radius.dot(radius);
    discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0){
      return false;
    } else {
    }
    return false;
  }

  void print(){
  }
protected:
};

class Plane : public GeomObj{
public:
protected:
};

class Group{
public:
  Vector<GeoObj*> members;
  bool hit(const Ray& ray, double& tmin, Hit& hit) const {
    //loop through members and call hit function on them
  }
protected:
}

class Light{
public:
  RGBColor color;
  Light(){};
protected:
};

class LightDirectional : public Light{;
public:
protected:
};

class ViewPlane{
public:
  int vres, hres;
  float pixelSize;
  ViewPlane(){
    vres = 600;
    hres = 800;
    pixelSize = .0033;
  }
};

class Camera{
public:
  Vec3f u, v, w, eye, lookAt, up;
  ViewPlane vp;
  Camera(){
    eye = Vec3f();
    lookAt = Vec3f(0.0f, 0.0f, -1.0f);
    up = Vec3f(0.0f, 1.0f, 0.0f);
    computeUVW();
  }
  Camera(Vec3f _eye){
    eye = _eye;
    lookAt = Vec3f(0.0f, 0.0f, -1.0f);
    up = Vec3f(0.0f, 1.0f, 0.0f);
    computeUVW();
  }
  Camera(Vec3f _eye, Vec3f _lookAt){
    eye = _eye;
    lookAt = _lookAt;
    up = lookAt * (lookAt + Vec3f(0.0f,0.0f,1.0f));
    computeUVW();
  }
  Camera(Vec3f _eye, Vec3f _lookAt, Vec3f _up){
    eye = _eye;
    lookAt = _lookAt;
    up = _up;
    computeUVW();
  }
  virtual Ray generateRay(float x, float y) = 0;
protected:
  computeUVW(){
    w = eye - lookAt;
    w.normalize();
    u = up * w;
    u.normalize();
    v = w * u;
    computeUVW();
  }
};

class CameraOrthographic : public Camera{
public:
  CameraOrthoGraphic(){
    eye = Vec3f();
    lookAt = Vec3f(0.0f, 0.0f, -1.0f);
    up = Vec3f(0.0f, 1.0f, 0.0f);
    computeUVW();
  }
  CameraOrthoGraphic(Vec3f _eye){
    eye = _eye;
    lookAt = Vec3f(0.0f, 0.0f, -1.0f);
    up = Vec3f(0.0f, 1.0f, 0.0f);
    computeUVW();
  }
  CameraOrthoGraphic(Vec3f _eye, Vec3f _lookAt){
    eye = _eye;
    lookAt = _lookAt;
    up = lookAt * (lookAt + Vec3f(0.0f,0.0f,1.0f));
    computeUVW();
  }
  CameraOrthoGraphic(Vec3f _eye, Vec3f _lookAt, Vec3f _up){
    eye = _eye;
    lookAt = _lookAt;
    up = _up;
    computeUVW();
  }
  Ray generateRay(float x, float y){
    //x = s(c - hres/2 + .5);
    //x = s((c - hres/2)*v + .5*v)
    //normally, shoot a ray through the center of a pixel x,y from the eye
    //direction is eye - lookAt vector, y moves along up vector, x moves along eye - lookAt x up (or u) 
    Ray retRay;
    
  }
protected:
};

class CameraPinhole : public Camera{
public:
protected:
};

class RGBColor{
public:
protected:
};

class Material{
public:
protected:
};

class MaterialPhong : public Material {
public:
protected:
};
