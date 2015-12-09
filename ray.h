#ifndef __RAY__
#define __RAY__

//#include "vec3.h"
class Vec3f;

class Ray{
public:
  Vec3f* o,* d; //origin and direction, respectively

  Ray(Vec3f* origin, Vec3f* dir){\
    o = new Vec3f();
    //o = origin;
    d = new Vec3f();
    //d = dir;
    //o = origin;
    //d = dir;
  }

  Ray(const Ray& ray){
    o = ray.o;
    d = ray.d;
  }

  Ray& operator=(const Ray& rhs){
    o = rhs.o;
    d = rhs.d;
  }


};

#endif
/*inline void assign(const VecN* rhs){
  for( int i = 0; i < length; i++ ){
    data[i] = rhs->data[i];
  }
}*/
