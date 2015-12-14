#ifndef __WORLD__
#define __WORLD__

#include <iostream>
#include <fstream>
#include <stdexcept>
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
  Light ambient;
  void render(Magick::Image& o, Magick::Image& depth);
  void buildTest();

  void build(std::string s);
//parse functions
  void parseCamera();
  void parseViewPlane();
  void parseLight();
  void parseBackground();
  void parsePhongMaterial();
  void parseMaterials();
  void parseSphere();
  void parsePlane();
  void parseObjects();

  bool readToken(std::string s);
  Vec3f parseVec3f();
  std::string check_token();

private:
  //1string m_next_token;
  //void reset();
  //int ptoken(string rexp); 
  //string peekat_token();
  int index;
  std::string file, token;
  std::ifstream if_stream;
};

#endif
