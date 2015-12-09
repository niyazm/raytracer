#ifndef __SHADEREC__
#define __SHADEREC__

#include "vec3.h"
//#include "rgbcolor.h"
//#include "world.h"

class World; //forward declaration
class RGBColor; //forward declarartion

class ShadeRec{
public:
  bool hit_an_object;
  Vec3f local_hit_point;
  Vec3f normal;
  RGBColor color;
  World& w;

  ShadeRec(World& wr){
    hit_an_object = false;
    color = Vec3f(0.0f, 0.0f, 0.0f);
    w(wr);
  }

  ShadeRec(const ShadeRec& sr){
    hit_an_object = sr.hit_an_object;
    local_hit_point = sr.local_hit_point;
    normal = sr.normal;
    color = sr.color;
    w = sr.w;
  }

  ShadeRec& operator=(const ShadeRec& rhs){
    hit_an_object = sr.hit_an_object;
    local_hit_point = sr.local_hit_point;
    normal = sr.normal;
    color = sr.color;
    w = sr.w;
  }
}

#endif
