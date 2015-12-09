#ifndef __RGBColor__
#define __RGBColor__

#include "vec3.h"

class RGBColor{
public:
  Vec3f color;

  float red, blue, green;

  RGBColor()
  {
    color = Vec3f(0.0f, 0.0f, 0.0f);
    setColor();
  }

  RGBColor(Vec3f rgb){
    color = rgb;
    setColor();
  }

  RGBColor& operator=(const Vec3f& v){
    color = v;
    setColor();
  }

  void print_color(int tabs){
    tabsting = "";
    for (int i = 0; i < tabs; i++){
      tabstring += "\t";
    }
    cout << tabstring << "RGBColor :" << endl;
    cout << tabstring << "\t" << "RGB :" << color << endl;

  }

private:
  setColor(){
    red = color[0];
    blue = color[1];
    green = color[2];
  }
}

#endif
