#include <iostream>
#include <fstream>
#include <string>
#include <Magick++.h>

//Utilities and basic stuff
#include "Vec3.hpp"
#include "RGBColor.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "ViewPlane.hpp"
#include "Ray.hpp"

//Geometric Objects
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Group.hpp"

//Lights
#include "Light.hpp"
#include "LightDirectional.hpp"

class World{
public:
  Camera camera;
  Group objects;
  std::vector<Material*> materials;
  std::vector<Light*> lights;
  RGBColor background; 
  void Render();
  void buildTest();
private:
  //1string m_next_token;
  //void reset();
  //int ptoken(string rexp); 
  //string peekat_token();
};

float clamp(float x, float min, float max){
  x = x > max ? max : x;
  x = x < min ? min : x;
  return x;
}

float colorClamp(float x){
  return clamp(x, 0, 1);
}

RGBColor minMaxClamp(RGBColor _c){
  return RGBColor(colorClamp(_c.r), colorClamp(_c.g), colorClamp(_c.b));  
}

Magick::ColorRGB RGBCtoCRGB(RGBColor _c){
  _c = minMaxClamp(_c);
  return Magick::ColorRGB(_c.r, _c.g, _c.b);
}
