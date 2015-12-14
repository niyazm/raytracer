#include "Camera.hpp"
#include <iostream>

Camera::Camera(Vec3f _e, Vec3f _look, Vec3f _u){
  eye = _e;
  lookAt = _look;
  up = _u;
  compute_UVW();
}

Camera::Camera(Vec3f _e, Vec3f _look){
  eye = _e;
  lookAt = _look;
  up = eye + Vec3f(0.0f, 1.0f, 0.0f);
  compute_UVW();
}

Camera::Camera(Vec3f _e){
  eye = _e;
  up = eye + Vec3f(0.0f, 1.0f, 0.0f);
  lookAt = Vec3f(0.0f, 0.0f, -1.0f);
  compute_UVW();
}

Camera::Camera(){
  eye = Vec3f(0.0f, 0.0f, 0.0f);
  up = eye + Vec3f(0.0f, 1.0f, 0.0f);
  lookAt = Vec3f(0.0f, 0.0f, -1.0f);
  compute_UVW();
}

void Camera::compute_UVW(){
  //W = eye - lookAt; //pointing in wrong direction??
	W = lookAt - eye;
  W.normalize();
  V = W * up;
  V.normalize();
  U = V * W;
  U.normalize();
}

Ray Camera::generateRay(int x, int y){
  bool DEBUG = false;
  Vec3f vpx = U;
  Vec3f vpy = V;
  if(x == 510 && y == 300){
    std::cout << vpx << vpy << std::endl;
    std::cout << "Dim: " << vp.hres << " " << vp.vres << std::endl;
  }
  float uAdjustment = vp.pixelSize * ( x - (vp.vres)*.5);
  float vAdjustment = vp.pixelSize * ( y - (vp.hres)*.5);
  if(x == 510 && y == 300){
    std::cout << "Adjustments in U and V:" << uAdjustment << " " << vAdjustment << std::endl;
  }
  vpx *= uAdjustment;
  vpy *= vAdjustment;
  Vec3f vpz = W;
  vpz *= vp.distance;
  if(x == 510 && y ==300){
    std::cout << "vp distance: " << vpz << vp.distance << std::endl;
  }
  Vec3f vpLoc = Vec3f(0,0,0);
  //Vec3f offset = Vec3f(0, 7, -7);
  vpLoc += vpx + vpy + vpz /*+ offset*/;
  if(x == 510 && y == 300){
    std::cout << "net adjustments" << vpx << vpy << vpz << std::endl;
  }
  Vec3f origin = vpLoc + eye;
  if(x ==510 && y ==300){
    std::cout << origin << "=" << vpLoc << "-" << eye << std::endl;
    std::cout << W << std::endl;
  }
  /*
  Vec3f adj = Vec3f(-vp.hres, -vp.vres, 0.0f)/2;
  Vec3f loc = Vec3f(x, y, 0);
  adj += loc;
  adj *= vp.pixelSize;
  adj += Vec3f(vp.pixelSize/2, vp.pixelSize/2, 0.0f);
	//double check this math with pictures
  Vec3f vpOrig = eye + W * (-vp.distance);
  Vec3f origin = vpOrig + adj;
  */
  Vec3f direction = W; //orthographic camera!
  if (DEBUG) {
    std::cout << "DIR: " << direction << " ";
    std::cout << "ORG: " << origin << std::endl;
  }
  return Ray(direction, origin);
}
