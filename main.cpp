/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <memory>
#include <tuple>
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include "Camera.h"
#include "Light.h"
#include "Manipulator.h"
#include "Mesh.h"
#include "Scene.h"
#include "ToonShaderNode.h"
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
    camera->SetEye(0, 0, 1);
    camera->SetCenter(0, 0, 0);
    camera->SetPerspective(50, 0.05, 5);
    scene->AddNode(camera);

    manipulator = new Manipulator();
    camera->SetManipulator(std::unique_ptr<Manipulator>(manipulator));

    auto light_t = std::make_shared<Transform>();
    light_t->Translate(0, 3, 0);
    scene->AddNode(light_t);

    auto light = std::make_shared<Light>();
    light_t->AddNode(light);

    auto bunny = std::make_shared<ToonShaderNode>();
    bunny->SetColor(0xAA55AA);
    bunny->SetMesh(std::make_shared<Mesh>("data/bunny.msh"));
    scene->AddNode(bunny);
}

