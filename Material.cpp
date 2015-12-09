#include "Material.hpp"

RGBColor Material::shade(){
  return RGBColor(Vec3f(1.0f, 0.0f, 0.0f));
}

RGBColor Material::area_light_shade(){
  return RGBColor(Vec3f(1.0f, 0.0f, 0.0f));
}

RGBColor Material::path_shade(){
  return RGBColor(Vec3f(1.0f, 0.0f, 0.0f));
}


