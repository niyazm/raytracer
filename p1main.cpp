
#include "World.hpp"
#include <string>
#include <iostream>
using namespace std;

class arguments{
public:
  string input, image_out, depth_out;
  bool verbose, help;

  arguments(string i = "scenein.txt", string i_o = "imageout.png", string d_o = "depthout.png", bool _v = false, bool _h = false){
    input = i;
    image_out = i_o;
    depth_out = d_o;
    verbose = _v;
    help = _h;
  }
};

void helpMessage(arguments a){
  if (a.help){
      cout << "This program reads in a scene using MIT's CSAIL grammar and renders it with an orthographic camera." << endl
      <<     "The following options are available:" << endl
      <<     "-i file (An input scene file. Use -i test to test the renderer.)" << endl
      <<     "-o file (An output image file.)" << endl
      <<     "-d file (An output depth image file.)" << endl
      <<     "-v (Turns on verbose logging.)" << endl
      <<     "-h (Displays this message.)" << endl;
    }
}

int main(int argc, char **argv){
	//parse -i, -o, -d, -v, and -h
  string input, outputimage, outputdepth;
  bool verbose = false, help = false;
  //parsing these could be a little more robust
  for (int i = 1; i < argc; i++){
    if(string(argv[i]) == "-i")
        input = string(argv[i+1]);
    if(string(argv[i])== "-o")
        outputimage = string(argv[i+1]);
    if(string(argv[i]) == "-d")
        outputdepth = string(argv[i+1]);
    if(string(argv[i]) == "-v")
        verbose = true;
    if(string(argv[i]) == "-v"){
        help = true;
    }
  }
  arguments args(input, outputimage, outputdepth, verbose, help);
  if(args.help){
    helpMessage(args);
    return 0;
  }
  /*std::ifstream inputFile(args.input.c_str(), std::ifstream::in);
  if(!inputFile){
  	std::cout << "could not open file" << std::endl;
  	return 1;
  }*/
  World raytracer;
  if(args.input == "test") {
  	raytracer.buildTest();
  }else{
  	raytracer.build(args.input);
  }
  Magick::InitializeMagick(*argv);
  Magick::Image output = Magick::Image(Magick::Geometry(raytracer.camera.vp.hres, raytracer.camera.vp.vres), "white");
  Magick::Image depth = Magick::Image(Magick::Geometry(raytracer.camera.vp.hres, raytracer.camera.vp.vres), "white");
  raytracer.render(output, depth);
  std::cout << "Finished rendering. Writing files." << std::endl;
  std::cout << args.image_out << " and " << args.depth_out << std::endl;
  if (args.image_out == ""){
  	output.write("scene.png");
  } else {
  	output.write(args.image_out);
  }
  if (args.depth_out == ""){
  	depth.write("depth.png");
  } else {
  	depth.write(args.depth_out);
  }
  return 0;
}

