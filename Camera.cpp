#include "Camera.hpp"

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
  W = eye - lookAt; //pointing in wrong direction??
	//W = lookAt - eye;
  W.normalize();
  U = up * W;
  U.normalize();
  V = W * U;
}

Ray Camera::generateRay(int x, int y){
  Vec3f adj = Vec3f(-vp.hres, -vp.vres, 0.0f)/2;
  Vec3f loc = Vec3f(x, y, 0);
  adj += loc;
  adj *= vp.pixelSize;
  adj += Vec3f(vp.pixelSize/2, vp.pixelSize/2, 0.0f);
	//double check this math with pictures
  Vec3f vpOrig = eye + W * (-vp.distance);
  Vec3f origin = vpOrig + adj;
  Vec3f direction = W * -1; //orthographic camera!
  return Ray(direction, origin);
}
