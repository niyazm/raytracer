#include "World.hpp"

int main(int argc, char **argv){
  World raytracer;
  raytracer.buildTest();
  Magick::InitializeMagick(*argv);
	Magick::Image output = Magick::Image(Magick::Geometry(raytracer.camera.vp.hres, raytracer.camera.vp.vres), "white");
  std::cout << output.columns() << "," << output.rows() << std::endl; 
  raytracer.render(output);
	output.write("test.png");
  return 0;
}
