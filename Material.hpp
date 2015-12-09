#ifndef __MATERIAL__
#define __MATERIAL__

#include "RGBColor.hpp"

class Material{
public:
  virtual RGBColor shade(Vec3f normal, Vec3f view);
  virtual RGBColor area_light_shade();
  virtual RGBColor path_shade();
 
protected:
};

#endif
