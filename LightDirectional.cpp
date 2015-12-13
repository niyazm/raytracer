#include "LightDirectional.hpp"

DirLight::DirLight(Vec3f d, RGBColor c){
  direction = d;
  colorA = colorS = colorD = c;
}

DirLight::DirLight(Vec3f d){
  direction = d;
  RGBColor c = RGBColor(Vec3f(1.0f, 1.0f, 1.0f));
  colorA = colorS = colorD = c;
}

DirLight::DirLight(){
  direction = Vec3f(0.0f, -1.0f, 0.0f);
  RGBColor c = RGBColor(Vec3f(1.0f, 1.0f, 1.0f));
  colorA = colorS = colorD = c;
}
