#ifndef __MATERIAL__
#define __MATERIAL__

#include "RGBColor.hpp"
#include "Light.hpp"
#include "LightDirectional.hpp"
#include <vector>

class Material{
public:
  RGBColor color;
  double a; //shininess constant
  Vec3f K; //reflectance constants
  Material();
  Material(RGBColor _c);
  virtual RGBColor shade(Vec3f normal, Vec3f view, Light ambient, DirLight L);
  //virtual RGBColor shade(Vec3f normal, Vec3f view, Light ambient, std::vector<Light*> lights);
  virtual RGBColor area_light_shade();
  virtual RGBColor path_shade();
 
protected:
};

#endif
