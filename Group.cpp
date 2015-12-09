#include "Group.hpp"

Group::Group(){
  if(objects.size() != 0){
    cleanUp();
  }
  objects.resize(0);
}

void Group::add_object(GeomObj* newObj){
  //add a new obj pointer. dont forget to delete it!
  objects.push_back(newObj);
}

Hit Group::hit(const Ray& ray) {
    Hit retHit;
    for (std::vector<GeomObj*>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Hit currHit = (*it)->hit(ray);
      if (currHit.t < retHit.t) {
        retHit = currHit;
      }
    }
    return retHit;
}

void Group::cleanUp(){
  for (std::vector<GeomObj*>::iterator it = objects.end(); it != objects.begin(); it--){
    delete (*it);
  }
}

Group::~Group(){
  cleanUp();
}
