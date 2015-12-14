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

bool World::readToken(std::string s){
  if_stream >> token;
  std::cout << "token: " << token << std::endl;
  return(s == token);
}

Vec3f World::parseVec3f() {
  float x, y, z;
  if_stream >> x >> y >> z;
  std::cout << "x,y,z:" << x << ", " << y << ", " << z << std::endl;
  return(Vec3f(x,y,z));
}

void World::parseCamera() {
  do {
  if(!readToken("OrthographicCamera")) break;//throw std::invalid_argument("received negative value");
  if(!readToken("{")) break;
  
  if(!readToken("center")) break;
  Vec3f eye = parseVec3f();

  if(!readToken("direction")) break;
  Vec3f direction = parseVec3f();

  if(!readToken("up")) break;
  Vec3f up = parseVec3f();

  if(!readToken("}")) break;

  camera = Camera(eye, direction, up);
  }while(0);
  std::cout << "Completed Parsing Camera" << std::endl;
}


void World::parseViewPlane() {
  do {
  if(!readToken("ViewPlane")) break;
  if(!readToken("{")) break;

  if(!readToken("width")) break;
  if_stream >> camera.vp.hres;
  std::cout << "hres: " << camera.vp.hres << std::endl;

  if(!readToken("height")) break;
  if_stream >> camera.vp.vres;
  std::cout << "vres: " << camera.vp.vres << std::endl;

  if(!readToken("pixelsize")) break;
  if_stream >> camera.vp.pixelSize;
  std::cout << "pixelSize: " << camera.vp.pixelSize << std::endl;

  if(!readToken("}")) break;
  }while(0);
  std::cout << "Completed Parsing View Plane" << std::endl;
}

void World::parseLight() {

}

void World::parseBackground() {
  do{
  if(!readToken("Background")) break;
  if(!readToken("{")) break;

  if(!readToken("color")) break;
  if_stream >> background.r >> background.g >> background.b;
  std::cout << "background RGB: " << background.r << ", " << background.g << ", " << background.b << std::endl;

  if(!readToken("}")) break;
  }while(0);
  std::cout << "Completed Parsing Background" << std::endl;
}

void World::parsePhongMaterial() {
  do {
  if(!readToken("PhongMaterial")) break;
  if(!readToken("{")) break;

  if(!readToken("diffuseColor")) break;
  materials.push_back(new Material(RGBColor(parseVec3f())));
  
  if(!readToken("}")) break;
  }while(0);
  std::cout << "Completed Parsing Phong" << std::endl;
}

void World::parseMaterials() {
  int n = 0;
  do{
  if(!readToken("Materials")) break;
  if(!readToken("{")) break;

  if(!readToken("numMaterials")) break;
  if_stream >> n;
  std::cout << "# of materials: " << n << std::endl;

  for(int i = 0; i < n; ++i)
    parsePhongMaterial();
  
  if(!readToken("}")) break;
  }while(0);
  std::cout << "Completed Parsing Materials" << std::endl;
}

std::string World::check_token(){
  std::string ret;
  if_stream >> ret;
  std::cout << "checked token: " << ret << std::endl;
  return(ret); 
}

void World::parseSphere() {
  Vec3f c;
  float r;
  do{
  //if(!readToken("Sphere")) break;
  if(!readToken("{")) break;
  
  if(!readToken("center")) break;
  c = parseVec3f();

  if(!readToken("radius")) break;
  if_stream >> r;
  std::cout << "radius: " << r << std::endl;
  std::cout << "material index: " << index << std::endl;
  objects.add_object(new Sphere(c, r, index));

  if(!readToken("}")) break;
  }while(0);
  std::cout << "Completed Parsing Spheres" << std::endl;
}

void World::parsePlane() {
  Vec3f _normal;
  float _offset;
  do{
  //if(!readToken("Plane")) break;
  if(!readToken("{")) break;

  if(!readToken("normal")) break;
  _normal = parseVec3f();

  if(!readToken("offset")) break;
  if_stream >> _offset;
  std::cout << "offset: " << _offset << std::endl;
  std::cout << "material index: " << index << std::endl;
  //objects.add_object(new Plane(_normal.normalize(), _offset, materials[index]));

  if(!readToken("}")) break;
  }while(0);
  std::cout << "Completed Parsing Planes" << std::endl;
}

void World::parseObjects() {
  do{
  if(!readToken("Group")) break;
  if(!readToken("{")) break;
  if(!readToken("numObjects")) break;
  if_stream >> token;
  std::cout << "# of objects: " << token << std::endl;
  bool more = true;
    do {
    std::string peek = check_token();
    if("MaterialIndex" == peek) if_stream >> index;
    else if("Sphere" == peek) parseSphere();
    else if("Plane" == peek) parsePlane();
    else if("}" == peek) more = false;
    else break;
    }while(more);
  }while(0);
  std::cout << "Completed Parsing Objects" << std::endl;
}

void World::build(std::string s) {

  /*std::cout << "Enter filename to parse: ";
  std::cin >> file;*/
  file = s;
  std::cout << "File to parse is :" << file << std::endl;
  if(file != "q" || "Q")
    if_stream.open(file);
  else
    std::cout << "User quit." << std::endl;
  if(!if_stream)
    std::cout << "Error parsing file." << std::endl;
  else {
    std::cout << "Starting Parse" << std::endl;
    //camera
    parseCamera();
    //viewplane
    parseViewPlane();
    //light
    //light.push_back(parseLight());
    //background
    parseBackground();
    //materials
    parseMaterials();
    //objects
    parseObjects();

    if_stream.close();

    ambient = Light(RGBColor(.1,.1,.1), RGBColor(.1,.1,.1), RGBColor(.1,.1,.1));
    lights.push_back(new DirLight(Vec3f(0.0f, 0.0f, -1.0f), RGBColor(1.0f)));
    objects.report();
    //std::cout << "index: " << index << std::endl;
  }
}

void World::buildTest(){
  //insert a single sphere into scene
  /*objects.add_object(new Sphere(Vec3f(0.0f, 0.0f, 0.0f), 1));
  objects.add_object(new Sphere(Vec3f(1.0f, 1.0f, 0.0f), 1));
  objects.add_object(new Sphere(Vec3f(2.0f, 2.0f, 1.50f), 1));*/
  //insert a camera and viewplane
  camera = Camera(Vec3f(30.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));
  camera.vp = ViewPlane(1900, 1080, .0165, .001);
  //add a light
  ambient = Light(RGBColor(.1,.1,.1), RGBColor(.1,.1,.1), RGBColor(.1,.1,.1)); //dim white light
  lights.push_back(new DirLight(Vec3f(0.0f, 0.0f, -1.0f), RGBColor(1,1,1))); //max white light shining down x axis UNUSED IN PROJ1
  //add a material
  materials.push_back(new Material(RGBColor(1, .000010, .000010)));
  materials.push_back(new Material(RGBColor(1, 1, .000010)));
  materials.push_back(new Material(RGBColor(0, 0, 1)));
  //add some objects
  for(int i = 0; i < 10; i ++){
    objects.add_object(new Sphere(Vec3f(i, i, i), .75, i%3));
  }
  objects.add_object(new Plane(Vec3f(1.6, 0, 1), Vec3f(0, 0, 0), 0));
  objects.add_object(new Plane(Vec3f(1, 1.5, 0), Vec3f(0, 0, 0), 1));
  objects.add_object(new Plane(Vec3f(1, -1, 0), Vec3f(-0, 0, 0), 2));
  objects.add_object(new Plane(Vec3f(1, 0, -1.25), Vec3f(-0, 0, 0), 1));
  objects.report();
  //choose black as BG color
  background = RGBColor(); //black
}

void World::render(Magick::Image& o, Magick::Image& depth){
  RGBColor outputColor, outputDepth;
  Magick::ColorRGB OC, OD; //output color in GraphicsMagick++'s object format
  Hit hitrec;
  Ray primaryRay;
  //Magick::Image output = Magick::Image(Magick::Geometry(camera.vp.hres, camera.vp.vres), "white");
  float tmax = 0.0f;
  float tmin = 10000.0f;
  RGBColor cmax = RGBColor(0, 0, 0);
  RGBColor cmin = RGBColor(1, 1, 1);
  /* LIGHT FOR PROJECT 1 SET HERE */
  DirLight L = DirLight(camera.eye, camera.lookAt, RGBColor(Vec3f(1,1,1)));
  for(int r = 0; r < camera.vp.vres; r++){
    for(int c = 0; c < camera.vp.hres; c++){
      primaryRay = camera.generateRay(c, r);
      hitrec = objects.hit(primaryRay);
      if(hitrec.t < 10000.0f ){
        //if (hitrec.t > .1) outputColor = hitrec.mat->shade(hitrec.normal, hitrec.view, ambient, L); //use normal and material to phong shade
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
  for(int r = 0; r < camera.vp.vres; r++){
    for(int c = 0; c < camera.vp.hres; c++){
      primaryRay = camera.generateRay(r, c);
      hitrec = objects.hit(primaryRay);
      if(hitrec.t < 10000.0f ){
        float tcol = 1-(hitrec.t - tmin)/(tmax - tmin);
        outputDepth = RGBColor(tcol,tcol,tcol);
        //outputColor = hitrec.mat->shade(hitrec.normal, hitrec.view, ambient, L); //use normal and material to phong shade
        outputColor = materials[hitrec.mat]->shade(hitrec, ambient, L); //use normal and material to phong shade
        //if (hitrec.point.components[1] == 0 || hitrec.point.components[2] == 0) outputColor = RGBColor(1,1,1);
        //outputColor.r = (outputColor.r - cmin.r)/(cmax.r - cmin.r);
        //outputColor.g = (outputColor.g - cmin.g)/(cmax.g - cmin.g);
        //outputColor.b = (outputColor.b - cmin.b)/(cmax.b - cmin.b);
      } else {
        outputColor = background;
        outputDepth = RGBColor(0,0,0);
      }
      //if(camera.vp.row(r) == 0 || camera.vp.col(c) == 0)outputColor = RGBColor(1,0,0);
      OC = RGBCtoCRGB(outputColor); //clamps colors to [0,1] and returns a ColorRGB
      OD = RGBCtoCRGB(outputDepth);
      o.pixelColor(c, camera.vp.vres-r-1, OC);
      depth.pixelColor(c, camera.vp.vres-r-1, OD);
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
