# PUC-Rio 2015.2
# INF1339 - Computação Gráfica Tridimensional
# Professor: Waldemar Celes
# Gabriel de Quadros Ligneul 1212560
# Trabalho - Projeto de Grafo de Cena

cc=g++
cflags=-O0 -g -Wall -Wextra -Werror -std=c++11
lflags=-lGL -lGLU -lGLEW -lglut
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
Mesh.o: Mesh.cpp vec3.h Mesh.h Shape.h
color.o: color.cpp color.h
Scene.o: Scene.cpp Environ.h Scene.h Group.h Node.h
Manipulator.o: Manipulator.cpp Manipulator.h invertMatrix.h vec3.h
Environ.o: Environ.cpp color.h Environ.h
Transform.o: Transform.cpp Manipulator.h Transform.h Group.h Node.h \
 invertMatrix.h
Camera.o: Camera.cpp Camera.h Node.h Manipulator.h
invertMatrix.o: invertMatrix.cpp invertMatrix.h
Group.o: Group.cpp Group.h Node.h
Texture.o: Texture.cpp lodepng.h Texture.h Appearance.h
Material.o: Material.cpp color.h Material.h Appearance.h
Light.o: Light.cpp Light.h Node.h
Entity.o: Entity.cpp Entity.h Node.h Appearance.h Shape.h
ToonShader.o: ToonShader.cpp ToonShader.h Appearance.h
main.o: main.cpp Camera.h Node.h Entity.h Environ.h Light.h Manipulator.h \
 Material.h Appearance.h Mesh.h vec3.h Shape.h Scene.h Group.h Texture.h \
 ToonShader.h Transform.h
lodepng.o: lodepng.cpp lodepng.h
Node.o: Node.cpp Node.h
