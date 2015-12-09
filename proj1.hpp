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

class Ray{
public:
  Vec3f o, d;
  Ray(){ };
  Ray(Vec3f _d);
  Ray(Vec3f _d, Vec3f _o);
protected:
};


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
  virtual bool hit(const Ray& ray, double& tmin, Hit& hit) const;
  void print();
protected:
};

class Plane : public GeomObj{
public:
protected:
};

class Group{
public:
  Vector<GeoObj*> members;
  bool hit(const Ray& ray, double& tmin, Hit& hit) const;
protected:
}

class Light{
public:
  RGBColor color;
  Light();
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
  ViewPlane();
};

class Camera{
public:
  Vec3f u, v, w, eye, lookAt, up;
  ViewPlane vp;
  Camera();
  Camera(Vec3f _eye);
  Camera(Vec3f _eye, Vec3f _lookAt);
  Camera(Vec3f _eye, Vec3f _lookAt, Vec3f _up);
  virtual Ray generateRay(float x, float y) = 0;
protected:
  computeUVW();
};

class CameraOrthographic : public Camera{
public:
  CameraOrthoGraphic()
  CameraOrthoGraphic(Vec3f _eye);
  CameraOrthoGraphic(Vec3f _eye, Vec3f _lookAt);
  CameraOrthoGraphic(Vec3f _eye, Vec3f _lookAt, Vec3f _up);
  Ray generateRay(float x, float y);
protected:
};

class CameraPinhole : public Camera{
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
