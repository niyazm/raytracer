#include "World.hpp"

int main(int argc, char **argv){
  World raytracer;
  raytracer.buildTest();
  Magick::InitializeMagick(*argv);
	Magick::Image output = Magick::Image(Magick::Geometry(800, 600), "white");
  raytracer.render(output);
	//output.write("test.png");
  return 0;
}
