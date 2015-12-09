#include "LightDirectional.hpp"

DirLight::DirLight(Vec3f d, RGBColor c){
  direction = d;
  color = c;
}

DirLight::DirLight(Vec3f d){
  direction = d;
  color = Vec3f(1.0f, 1.0f, 1.0f);
}

DirLight::DirLight(){
  direction = Vec3f(0.0f, -1.0f, 0.0f);
  color = Vec3f(1.0f, 1.0f, 1.0f);
}
