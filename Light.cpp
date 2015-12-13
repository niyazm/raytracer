#include "Light.hpp"

Light::Light(RGBColor c){
  Light(c, c, c);
}

Light::Light(){
  Light(RGBColor(1,1,1));
}

Light::Light(RGBColor a, RGBColor d, RGBColor s){
  colorA = a;
  colorD = d;
  colorS = s;
}
