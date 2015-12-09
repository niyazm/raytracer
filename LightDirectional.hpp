#ifndef __DLIGHT__
#define __DLIGHT__

#include "Light.hpp"

class DirLight : public Light{
public:
  Vec3f direction;
  DirLight();
  DirLight(Vec3f d);
  DirLight(Vec3f d, RGBColor c);
protected:
};

#endif
