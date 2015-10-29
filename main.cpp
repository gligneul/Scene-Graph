/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <memory>
#include <tuple>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Camera.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Entity.h"
#include "Environ.h"
#include "Light.h"
#include "Manipulator.h"
#include "Material.h"
#include "Mesh.h"
#include "Scene.h"
#include "Sphere.h"
#include "Texture.h"
#include "ToonShader.h"
#include "Transform.h"

/* Scene nodes */
static Scene* scene = nullptr;
static Manipulator* manipulator = nullptr;

/* Auxiliary functions and glut callbacks */
static void Display();
static void Keyboard(unsigned char key, int x, int y);
static void Mouse(int button, int state, int x, int y);
static void Motion(int x, int y);
static void CreateScene();

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Scene Graph");
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << "\n";
        exit(1);
    }
    ToonShader::Init();
    CreateScene();
    glutMainLoop();
    return 0; 
}
    
static void Display() {
    scene->Render();
    glutSwapBuffers();
}

static void Keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'q': {
            delete scene;
            exit(0);
            break;
        }
    }
    glutPostRedisplay();
}

static void Mouse(int button, int state, int x, int y) {
    manipulator->GlutMouse(button, state, x, y);
    glutPostRedisplay();
}

static void Motion(int x, int y) {
    manipulator->GlutMotion(x, y);
    glutPostRedisplay();
}

static void CreateScene() {
    scene = new Scene();

    auto camera = std::make_shared<Camera>();
    camera->SetEye(-1, 0, 0);
    camera->SetCenter(0, 0, 0);
    camera->SetPerspective(50, 0.05, 5);
    scene->AddNode(camera);

    manipulator = new Manipulator();
    camera->SetManipulator(std::unique_ptr<Manipulator>(manipulator));

    auto light_t = std::make_shared<Transform>();
    light_t->Translate(0, 2, 0);
    scene->AddNode(light_t);

    auto light = std::make_shared<Light>();
    light_t->AddNode(light);

    auto bunny = std::make_shared<Entity>();
    bunny->SetAppearance(std::make_shared<ToonShader>());
    bunny->SetShape(std::make_shared<Mesh>("bunny.off"));
    scene->AddNode(bunny);
}

