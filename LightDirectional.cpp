#include "LightDirectional.hpp"

DirLight::DirLight(Vec3f d, RGBColor c){
  direction = d;
  direction.normalize();
  colorA = colorS = colorD = c;
}

DirLight::DirLight(Vec3f p, Vec3f d, RGBColor c){
  direction = d;
  pos = p;
  direction.normalize();
  colorA = colorS = colorD = c;
}

DirLight::DirLight(Vec3f d){
  direction = d;
  direction.normalize();
  RGBColor c = RGBColor(Vec3f(1.0f, 1.0f, 1.0f));
  colorA = colorS = colorD = c;
}

DirLight::DirLight(){
  direction = Vec3f(0.0f, -1.0f, 0.0f);
  RGBColor c = RGBColor(Vec3f(1.0f, 1.0f, 1.0f));
  colorA = colorS = colorD = c;
}
