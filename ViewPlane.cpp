#include "ViewPlane.hpp"

ViewPlane::ViewPlane(int h, int v, float s, float d){
  hres = h;
  vres = v;
  pixelSize = s;
  distance = d;
}

ViewPlane::ViewPlane(int h, int v, float s){
  hres = h;
  vres = v;
  pixelSize = s;
  distance = .001f;
}

ViewPlane::ViewPlane(int h, int v){
  ViewPlane(h, v, .0033);
}

ViewPlane::ViewPlane(){
  ViewPlane(800, 600);
}
