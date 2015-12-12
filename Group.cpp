#include "Group.hpp"

Group::Group(){
  if(geomObjs.size() != 0){
    cleanUp();
  }
  geomObjs.resize(0);
}

void Group::add_object(GeomObj* newObj){
  //add a new obj pointer. dont forget to delete it!
  geomObjs.push_back(newObj);
}

Hit Group::hit(const Ray& ray) {
    Hit retHit;
    for (std::vector<GeomObj*>::iterator it = geomObjs.begin(); it != geomObjs.end(); it++)
    {
      Hit currHit = (*it)->hit(ray);
      if (currHit.t < retHit.t) {
        retHit = currHit;
      }
    }
    return retHit;
}

void Group::report() {
    Hit retHit;
    for (std::vector<GeomObj*>::iterator it = geomObjs.begin(); it != geomObjs.end(); it++)
    {
      (*it)->report();
    }
}

void Group::cleanUp(){
  /*for (std::vector<GeomObj*>::iterator it = geomObjs.end(); it != geomObjs.begin(); it--){
    delete (*it);
  }*/
}

Group::~Group(){
  cleanUp();
}
