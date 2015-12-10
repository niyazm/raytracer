#ifndef __WORLD__
#define __WORLD__

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
  void render(Magick::Image& o);
  void buildTest();
private:
  //1string m_next_token;
  //void reset();
  //int ptoken(string rexp); 
  //string peekat_token();
};

#endif
