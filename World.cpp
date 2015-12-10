#include "World.hpp"
#include <Magick++.h>


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

void World::buildTest(){
  //insert a single sphere into scene
  objects.add_object(new Sphere(Vec3f(0.0f, 0.0f, -1.0f), 1.0f));
  //insert a camera and viewplane
  camera = Camera(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, -1.0f), Vec3f(0.0f, 1.0f, 0.0f));
  camera.vp = ViewPlane(800, 600, .0033, .001);
  //add a light
  lights.push_back(new DirLight(Vec3f(0.0f, 0.0f, -1.0f), RGBColor(1.0f)));
  //choose black as BG color
  background = RGBColor(); //black
}

void World::render(Magick::Image& o){
  RGBColor outputColor;
  //Magick::ColorRGB OC; //output color in GraphicsMagick++'s object format
  Hit hitrec;
  Ray primaryRay;
  //Magick::Image output = Magick::Image(Magick::Geometry(800, 600), "white");
  for(int r = 0; r < camera.vp.hres; r++){
    for(int c = 0; c < camera.vp.vres; c++){
      primaryRay = camera.generateRay(r, c);
      hitrec = objects.hit(primaryRay);
      if(hitrec.mat != NULL){
        outputColor = hitrec.mat->shade(hitrec.ray, hitrec.normal); //use normal and material to phong shade
      } else {
        outputColor = background;
      }
      //OC = RGBCtoCRGB(outputColor); //clamps colors to [0,1] and returns a ColorRGB
     // output.pixelColor(r, c, OC);//fill in arguments
     // o.pixelColor(r, c, OC);//fill in arguments
    }
  }
  //output.write("test.png"); //args go here
}

/*
void World::reset(){
  m_next_token = "";
}

int World::ptoken(string rexp){
  string stoken = m_next_token;
  if ("" == stoken){
    g_fin >> stoken;
  } else {
    m_next_token = "";
  }
  if (rexp != stoken) {
    perr( rexp, stoken );
  }
}

string World::peekat_token(){
  string stoken;
  g_fin >> stoken;
  m_next_token = stoken;
  return stoken;
}

Vec3f World::_parseVec3f(){
  float x,y,z;
  g_fin >> x >> y >> z;
  return Vec3f(x, y, z);
}

void World::_parsePhongMaterial(int id){
}

void World::_parseMaterials(){
  int num = 0;
  do { //once
    if ( !ptoken("Materials")) break;
    if ( !ptoken("{")) break;
    if ( !ptoken("numMaterials")) break; 
    g_fin >> num;
    for(int id = 0; id < num; ++id){
      _parsePhongMaterial(id);
    }
    if ( !ptoken("}"))break;
  }while( 0 ); //once
} 

void World::_parseBackground(){
  do{ //once
    if(!ptoken("Background") break;
    if(!ptoken("{") break;
    if(!ptoken("color") break;
    Vec3f col = _parseVec3f();
    if(!ptoken("}") break;
  }while(0); //once
  RGBColor = bg(col);
  background = bg;
}

void World::_parseViewPlane(){
  int width, height;
  float size;
  do { //once
    if(!ptoken("ViewPlane"))break;
    if(!ptoken("{"))break;
    if(!ptoken("width"))break;
    g_fin >> width;
    if(!ptoken("height"))break;
    g_fin >> height;
    if(!ptoken("pixelsize"))break;
    g_fin >> size;
    if(!ptoken("}"))break;
  }while(0); //once
  w.camera.vp.hres = width;
  w.camera.vp.vres = height;
  w.camera.vp.pixelSize = size;
}

void World::_parseCamera(){
  do { //once
    if(!ptoken("OrthographicCamera"))break;
    if(!ptoken("{"))break;
    if(!ptoken("center"))break;
    Vec3f center = _parseVec3f();
    if(!ptoken("direction"))break;
    Vec3f direction = _parseVec3f();
    if(!ptoken("up"))break;
    Vec3f up = _parseVec3f();
    if(!ptoken("}"))break;
  }while(0); //once
  camera = Camera(center, direction, up); 
}


void World::_parsePlane(){

}

void World::_parseSphere(){

}

void World::_parseMaterialIndex(){

}

void World::_parseGroup(){

}

void World::open_file_from_user(){

}

void World::listen(){

}

void World::parse_file(){
  g_fin.open(inputFile.c_str());
  if(!g_fin){
    perr("File open");
  }
  if (g_fin) {
    reset();
    _parseCamera();
    _parseViewPlane();
    _parseBackground();
    _parseMaterials();
    _parseGroup();
    g_fin.close();
  }
}
*/
