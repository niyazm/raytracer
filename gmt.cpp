#include <Magick++.h>
#include <iostream>

using namespace Magick;
using namespace std;

int main(int argc, char **argv)
{
  	InitializeMagick(*argv);
	Image output = Magick::Image(Magick::Geometry(100, 100), "white");
  	cout << output.columns() << "," << output.rows() << endl; 
  	for(int i = 0; i < 100; i++){
  		output.pixelColor(i,i, "black");
  	}
	output.write("gmt.png");
  	return 0;
}