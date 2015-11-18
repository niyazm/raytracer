//super basic camera class for project 1
#ifndef __CAMERA__
#define __CAMERA__

#include "vec3.h"
#include <iostream>
#include <string>
using namespace std;

class Camera{
public:
  Vec3f u, v, w;
  Vec3f lookAt;
  Vec3f up;
  Vec3f eye;
  float exposure_time;

  Camera(Vec3f _c = Vec3f(0.0f, 0.0f, 0.0f),Vec3f _d = Vec3f(1.0f, 0,0f, 0,0f) ,Vec3f _u = Vec3f(0.0f, 1,0f, 0,0f) )
  {
    eye = _c;
    lookAt = _d;
    up = _u;
    compute_uvw();
  }

  void compute_uvw(){
    w = eye - lookAt;
    w.normalize();
    u = up * w;
    u.normalize();
    v = w * u;
  }

  void print_camera(int tabs){
    tabsting = "";
    for (int i = 0; i < tabs; i++){
      tabstring += "\t";
    }
    cout << tabstring << "CAMERA :" << endl;
    cout << tabstring << "\t" << "u:" << u << " v:" << v << " w:" << w << endl;
    cout << tabstring << "\t" << "lookAt: " << lookAt << endl;
    cout << tabstring << "\t" << "eye: " << eye << endl;
    cout << tabstring << "\t" << "up: " << up << endl;

  }
};

#endif
