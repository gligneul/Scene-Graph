# PUC-Rio 2015.2
# INF1339 - Computação Gráfica Tridimensional
# Professor: Waldemar Celes
# Gabriel de Quadros Ligneul 1212560
# Trabalho - Projeto de Grafo de Cena

cc=g++
cflags=-O2 -g -Wall -Wextra -Werror -std=c++11
lflags=-lGL -lGLU -lglut
target=scenegraph
src=$(wildcard *.cpp)
obj=$(src:.cpp=.o)

all: $(target)

$(target): $(obj)
	$(cc) $(lflags) -o $@ $^

depend: $(src)
	@$(cc) $(cflags) -MM $^
	
clean:
	@rm -rf *.o $(target)

%.o: %.cpp
	$(cc) $(cflags) -c -o $@ $<

# Dendencies (use 'make depend' to update)
Camera.o: Camera.cpp Camera.h Node.h Manipulator.h
Cube.o: Cube.cpp Cube.h Shape.h
Cylinder.o: Cylinder.cpp Cylinder.h Shape.h
Entity.o: Entity.cpp Entity.h Node.h Appearance.h Shape.h
Group.o: Group.cpp Group.h Node.h
Light.o: Light.cpp Light.h Node.h
main.o: main.cpp Camera.h Node.h Cube.h Shape.h Cylinder.h Entity.h \
 Light.h Manipulator.h Material.h Appearance.h Scene.h Group.h Sphere.h \
 Transform.h
Manipulator.o: Manipulator.cpp Manipulator.h mvector.h
Material.o: Material.cpp Material.h Appearance.h
Node.o: Node.cpp Node.h
Scene.o: Scene.cpp Environ.h Scene.h Group.h Node.h
Sphere.o: Sphere.cpp Sphere.h Shape.h
Transform.o: Transform.cpp Manipulator.h Transform.h Group.h Node.h
