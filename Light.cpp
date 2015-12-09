#include "Light.hpp"

Light::Light(RGBColor c){
  color = c;
}

Light::Light(){
  Light(Vec3f(1.0f, 1.0f, 1.0f));
}
