#ifndef __WORLD__
#define __WORLD__

#include "viewplane.h"
#include "rgbcolor.h"
#include "sphere.h"
#include "tracer.h"
#include "camera.h"
#include "geometricobject.h"
#include <iostream>
#include <vector>
using namespace std;

class World {
public:
  ViewPlane vp;
  RGBColor background_color;
  Sphere sphere;
  Tracer* tracer_ptr;
  Camera* camera_ptr;
  vector<GeometricObject*> objects;
  //vector<Light*> lights; //unnecessary for this project
  Light lights;

  World(void);

  void build (void);

  void render_scene(void) const;

  void open_window(const int hres, const int vres) const;

  void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

  void add_

  void print_world(){
    cout << "WORLD : " << endl;
    cout << "\t ";
    camera_ptr->print_camera(1);
    cout << "\t";
    cout << background_color.print_color(1);
    cout << "\t";
    cout << vp.print_viewPlane(1);
    cout << "\t";
    //for each light, print the light
    //for(vector<Light>::iterator it = lights.begin(); it++){}
    cout << "\t";
    cout << lights.print_light(1);
    //for each geometric object, print the object
    cout << "\t";
    for(vector<GeometricObject*>::iterator it = objects.begin(); it++){
      cout << it->print_object(1);
    }
  }
}

#endif __WORLD__
