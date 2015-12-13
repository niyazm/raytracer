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
  /*objects.add_object(new Sphere(Vec3f(0.0f, 0.0f, 0.0f), 1));
  objects.add_object(new Sphere(Vec3f(1.0f, 1.0f, 0.0f), 1));
  objects.add_object(new Sphere(Vec3f(2.0f, 2.0f, 1.50f), 1));*/
  //insert a camera and viewplane
  camera = Camera(Vec3f(30.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));
  camera.vp = ViewPlane(1000, 600, .033, .001);
  //add a light
  ambient = Light(RGBColor(.1,.1,.1), RGBColor(.1,.1,.1), RGBColor(.1,.1,.1));
  lights.push_back(new DirLight(Vec3f(0.0f, 0.0f, -1.0f), RGBColor(1.0f)));
  //add a material
  materials.push_back(new Material(RGBColor(1, .000010, .000010)));
  //add some objects
  for(int i = 0; i < 10; i ++){
    objects.add_object(new Sphere(Vec3f(i, i, i), .75, materials[0]));
  }
  //objects.add_object(new Plane(Vec3f(1, 0, 1), Vec3f(15, 0, 0), materials[0]));
  //objects.add_object(new Plane(Vec3f(1, 1, 0), Vec3f(15, 0, 0), materials[0]));
  //objects.add_object(new Plane(Vec3f(1, -1, 0), Vec3f(15, 0, 0), materials[0]));
  //objects.add_object(new Plane(Vec3f(1, 0, -1), Vec3f(15, 0, 0), materials[0]));
  objects.report();
  //choose black as BG color
  background = RGBColor(); //black
  std::cout << camera.eye << camera.lookAt << std::endl;
  std::cout << camera.U << camera.V << camera.W << std::endl;
}

void World::render(Magick::Image& o){
  RGBColor outputColor;
  Magick::ColorRGB OC; //output color in GraphicsMagick++'s object format
  Hit hitrec;
  Ray primaryRay;
  //Magick::Image output = Magick::Image(Magick::Geometry(camera.vp.hres, camera.vp.vres), "white");
  float tmax = 0.0f;
  float tmin = 10000.0f;
  RGBColor cmax = RGBColor(0, 0, 0);
  RGBColor cmin = RGBColor(1, 1, 1);
  DirLight L = DirLight(Vec3f(0, -1, 0), RGBColor(Vec3f(1,0,0)));
  for(int r = 0; r < o.rows(); r++){
    for(int c = 0; c < o.columns(); c++){
      primaryRay = camera.generateRay(c, r);
      hitrec = objects.hit(primaryRay);
      if(hitrec.t < 10000.0f ){
        outputColor = hitrec.mat->shade(hitrec.normal, hitrec.view, ambient, L); //use normal and material to phong shade
        if (hitrec.t > tmax) tmax = hitrec.t;
        if (hitrec.t < tmin) tmin = hitrec.t;
        if (outputColor.r > cmax.r) cmax.r = outputColor.r;
        if (outputColor.g > cmax.g) cmax.g = outputColor.g;
        if (outputColor.b > cmax.b) cmax.b = outputColor.b;
        if (outputColor.r < cmin.r) cmin.r = outputColor.r;
        if (outputColor.g < cmin.g) cmin.g = outputColor.g;
        if (outputColor.b < cmin.b) cmin.b = outputColor.b;
      }
    }
  }
  for(int r = 0; r < o.rows(); r++){
    for(int c = 0; c < o.columns(); c++){
      primaryRay = camera.generateRay(r, c);
      hitrec = objects.hit(primaryRay);
      //std::cout << primaryRay.d << primaryRay.o << " " << c << ", " << r << " " << " " << hitrec.t << std::endl;
      //if(hitrec.t < 10000.0f ) std::cout << " HIT!";
      //std::cout << std::endl;
      if(hitrec.t < 10000.0f ){
				//std::cout  << "HIT!" << std::endl;
        float tcol = 1-(hitrec.t - tmin)/(tmax - tmin);
        outputColor = RGBColor(tcol,tcol,tcol);
        std::cout << "Shading..." << std::endl;
        std::cout << "hr" << std::endl << "\t\t" << hitrec.normal << hitrec.view << std::endl;
        outputColor = hitrec.mat->shade(hitrec.normal, hitrec.view, ambient, L); //use normal and material to phong shade
        outputColor.r = (outputColor.r - cmin.r)/(cmax.r - cmin.r);
        //outputColor.g = (outputColor.g - cmin.g)/(cmax.g - cmin.g);
        //outputColor.b = (outputColor.b - cmin.b)/(cmax.b - cmin.b);
        std::cout << "done shading this pixel" << outputColor.r << " " << outputColor.g << " " << outputColor.b << std::endl;
      } else {
        outputColor = background;
      }
      if(camera.vp.row(r) == 0 || camera.vp.col(c) == 0)outputColor = RGBColor(1,0,0);
      OC = RGBCtoCRGB(outputColor); //clamps colors to [0,1] and returns a ColorRGB
      o.pixelColor(c, r, OC);//fill in arguments
      if(r == 1799 && c == 599) std::cout << "made it!" << std::endl;
    }
  }
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
