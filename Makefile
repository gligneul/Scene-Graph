# PUC-Rio 2015.2
# INF1339 - Computação Gráfica Tridimensional
# Professor: Waldemar Celes
# Gabriel de Quadros Ligneul 1212560
# Trabalho - Projeto Final

cc=g++
cflags=-O0 -g -Wall -Wextra -Werror -std=c++11
iflags=-I./lib
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
	$(cc) $(cflags) $(iflags) -c -o $@ $<

# Dendencies (use 'make depend' to update)
Mesh.o: Mesh.cpp Mesh.h
Engine.o: Engine.cpp Engine.h Transform.h Group.h Node.h
Scene.o: Scene.cpp Scene.h Group.h Node.h
Manipulator.o: Manipulator.cpp Manipulator.h
ShaderProgram.o: ShaderProgram.cpp ShaderProgram.h
Transform.o: Transform.cpp Manipulator.h Transform.h Group.h Node.h
Camera.o: Camera.cpp Camera.h Node.h Manipulator.h
Light.o: Light.cpp Light.h Node.h
Group.o: Group.cpp Group.h Node.h
Node.o: Node.cpp Node.h
main.o: main.cpp Camera.h Node.h Engine.h Transform.h Group.h Light.h \
 Manipulator.h Mesh.h Scene.h ToonShaderNode.h
ToonShaderNode.o: ToonShaderNode.cpp Mesh.h ShaderProgram.h \
 ToonShaderNode.h Node.h
