#ifndef __LIGHT__
#define __LIGHT__

#include "RGBColor.hpp"
//ambient light class. no location of light.

class Light{
public:
  RGBColor color;
  Light();
  Light(RGBColor c);
protected:
};

#endif
