#include <Magick++.h>
#include <iostream>
using namespace std;
using namespace Magick;

int main(int argc, char **argv)
{
  InitializeMagick(*argv);
  Image image;
  try{
    image = Image(Geometry(800, 600), "white");
    image.pixelColor(49,49, "red");
    for (int i = 0; i < 700; i++){
      for (int j = 0; j < 500; j++){
        if (i % 2 == 0){
          image.pixelColor(i, j, ColorRGB(1.0,0.0,1.0));
        } else {
          image.pixelColor(i, j, "white");
        }
      }
    }
    image.write("gmttest.png");
  }
  catch(Exception &error_)
  {
    cout << "CAught exception" << error_.what() << endl;
    return 1;
  }
  /*
  try {
    image.read("test.jpg");
    image.crop(Geometry(100,100,100,100));
    image.write("x.jpeg");
  }
  catch(Exception &error_)
  {
    cout << "Caught exception" << error_.what() << endl;
    return 1;
  }*/
  return 0;
}
