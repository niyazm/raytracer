#include "Material.hpp"
#include <vector>


Material::Material(){
  color = RGBColor(1, 0, 0);
}

Material::Material(RGBColor _c){
  color = _c;
}

RGBColor Material::shade(Hit h, /*Vec3f normal, Vec3f view,*/ Light ambient, DirLight L /*std::vector<Light*> L*/){
  double ka, kd, ks;
  ka = kd = ks = .1;
  kd = .4;
  RGBColor retVal = ambient.colorA;
  Vec3f Lm = L.pos - h.point; //direction from point to light loc
  Lm.normalize();
  double diffuse = Lm.dot(h.normal) * kd;
  retVal = color * L.colorD * diffuse * Lm.dot(h.normal);
  return retVal;
}

RGBColor Material::area_light_shade(){
  return RGBColor(Vec3f(1.0f, 0.0f, 0.0f));
}

RGBColor Material::path_shade(){
  return RGBColor(Vec3f(1.0f, 0.0f, 0.0f));
}


