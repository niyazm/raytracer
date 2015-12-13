CC=clang
CXX=clang++

CFLAGS += -g -std=c++11 -Wall -pedantic -pipe -I/opt/local/include
LDFLAGS += -g -Wall -pipe -L/opt/local/lib
LLDLIBS += -lGraphicsMagick++ #-lGL -lX11 -lGLU -lglfw3 -lXxf86vm -lpthread -lXrandr -lGLEW -lXi

CXXFILES  = Camera.cpp Group.cpp Hit.cpp Light.cpp LightDirectional.cpp Material.cpp Plane.cpp Ray.cpp RGBColor.cpp Sphere.cpp Vec3.cpp ViewPlane.cpp World.cpp p1main.cpp
HEADERS = Camera.hpp GeomObj.hpp Group.hpp Hit.hpp Light.hpp LightDirectional.hpp Material.hpp Plane.hpp Ray.hpp RGBColor.hpp Sphere.hpp Vec3.hpp ViewPlane.hpp World.hpp
TARGET = p1

OBJECTS = $(CXXFILES:.cpp=.o) $(CFILES:.c=.o)

DEP = $(CXXFILES:.cpp=.d) $(CFILES:.c=.d)

default all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LLDLIBS)

%.d: %.cpp
	set -e; $(CXX) -MM $(CFLAGS) $< \
	| sed 's/($*).o[ :]*/.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@

%.d: %.c
	set -e; $(CXX) -MM $(CFLAGS) $< \
	| sed 's/($*).o[ :]*/.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

%.o: %.c
	$(CXX) $(CFLAGS) -c $<

clean:
	-rm -f $(OBJECTS) core $(TARGET).core *~

spotless: clean
	-rm -f $(TARGET) $(DEP)