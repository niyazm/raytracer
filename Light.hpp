#ifndef __LIGHT__
#define __LIGHT__

#include "RGBColor.hpp"
//ambient light class. no location of light.

class Light{
public:
  RGBColor colorA;
  RGBColor colorD;
  RGBColor colorS;
  Light();
  Light(RGBColor c);
  Light(RGBColor a, RGBColor d, RGBColor s);
protected:
};

#endif
