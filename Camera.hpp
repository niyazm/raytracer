#ifndef __CAMERA__
#define __CAMERA__

#include "Vec3.hpp"
#include "ViewPlane.hpp"
#include "Ray.hpp"

class Camera{
public:
  Vec3f eye, lookAt, up;
  Vec3f U, V, W;  
	Camera();
	Camera(Vec3f _e);
	Camera(Vec3f _e, Vec3f _look);
	Camera(Vec3f _e, Vec3f _look, Vec3f _u);
	ViewPlane vp;
  virtual Ray generateRay(int x, int y) ;
protected:
	void compute_UVW();
};

#endif
