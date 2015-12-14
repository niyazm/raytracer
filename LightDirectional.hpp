#ifndef __DLIGHT__
#define __DLIGHT__

#include "Light.hpp"

class DirLight : public Light{
public:
  Vec3f direction;
  Vec3f pos;
  DirLight();
  DirLight(Vec3f d);
  DirLight(Vec3f d, RGBColor c);
  DirLight(Vec3f p, Vec3f d, RGBColor c);
protected:
};

#endif
