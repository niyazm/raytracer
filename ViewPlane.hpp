#ifndef __VIEWPLANE__
#define __VIEWPLANE__

class ViewPlane{
public:
  int hres, vres;
  float pixelSize;
  float distance; //distance from camera eye
  ViewPlane();
  int row(int x);
  int col(int x);
  ViewPlane(int h, int v);
  ViewPlane(int h, int v, float s);
  ViewPlane(int h, int v, float s, float d);
protected:
};

#endif 
