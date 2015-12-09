#ifndef __GROUP__
#define __GROUP__

#include <vector>
#include "GeomObj.hpp"

class Group : public GeomObj{
public:
  virtual Hit hit(const Ray& ray);
  std::vector<GeomObj*> objects; //wnat to change to a map
  void add_object(GeomObj* newObj);
  ~Group();
  Group();
protected:
  void cleanUp();
};

#endif
