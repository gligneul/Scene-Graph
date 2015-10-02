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
#include "Transform.h"

/* Constants */
static const float TABLE_HEIGHT = 100;

/* Scene nodes */
static Scene* scene = nullptr;
static Camera* global_camera = nullptr;
static Camera* lamp_camera = nullptr;
static Manipulator* global_manipulator = nullptr;
static Manipulator* lamp_manipulator = nullptr;
static Manipulator* curr_manipulator = nullptr;

/* Auxiliary functions and glut callbacks */
static void Display();
static void Keyboard(unsigned char key, int x, int y);
static void Mouse(int button, int state, int x, int y);
static void Motion(int x, int y);
static void CreateScene();
static Node* CreateTable(float height);
static std::tuple<Node*, Camera*, Manipulator*> CreateLamp();

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
            exit(0);
            break;
        }
        case 'c': {
            bool is_global_active = global_camera->GetActive();
            global_camera->SetActive(!is_global_active);
            lamp_camera->SetActive(is_global_active);
            if (is_global_active)
                curr_manipulator = lamp_manipulator;
            else
                curr_manipulator = global_manipulator;
            glutPostRedisplay();
            break;
        }
    }
}

static void Mouse(int button, int state, int x, int y) {
    curr_manipulator->GlutMouse(button, state, x, y);
    glutPostRedisplay();
}

static void Motion(int x, int y) {
    curr_manipulator->GlutMotion(x, y);
    glutPostRedisplay();
}

static void CreateScene() {
    scene = new Scene();

    auto environ = new Environ();
    environ->SetBackgroundColor(0xB1F1FF);
    environ->SetAmbient(0.2, 0.2, 0.2);
    environ->SetFog(0xB1F1FF, 100, 500);
    scene->SetEnviron(std::unique_ptr<Environ>(environ));

    float center[3] = {0, 100, 0};

    global_camera = new Camera();
    global_camera->SetEye(130, 200, 130);
    global_camera->SetCenter(center[0], center[1], center[2]);
    global_camera->SetPerspective(50, 5, 500);
    scene->AddNode(global_camera);

    curr_manipulator = global_manipulator = new Manipulator();
    global_manipulator->SetReferencePoint(center[0], center[1], center[2]);
    global_camera->SetManipular(global_manipulator);

    auto light_t = new Transform();
    light_t->Translate(0, 200, 0);
    scene->AddNode(light_t);

    auto light = new Light();
    light_t->AddNode(light);

    auto light_sphere = new Entity();
    light_sphere->SetAppearance(new Material(0xFFFFFF));
    light_sphere->SetShape(new Sphere(3));
    light_t->AddNode(light_sphere);

    auto floor = new Entity();
    floor->SetAppearance(new Material(0xE1F4C4));
    floor->SetShape(new Cube(500, 0.1, 500));
    scene->AddNode(floor);

    auto table_top = new Transform();
    table_top->Translate(0, TABLE_HEIGHT, 0);
    scene->AddNode(table_top);

    auto table = CreateTable(TABLE_HEIGHT);
    table_top->AddNode(table);

    auto lamp_t = new Transform();
    lamp_t->Translate(-30, 0, 30);
    lamp_t->Rotate(135, 0, 1, 0);
    table_top->AddNode(lamp_t);

    auto lamp = CreateLamp();
    lamp_t->AddNode(std::get<0>(lamp));
    lamp_camera = std::get<1>(lamp);
    lamp_manipulator = std::get<2>(lamp);

    auto ball_t = new Transform();
    ball_t->Translate(15, 5, 15);
    table_top->AddNode(ball_t);

    auto ball = new Entity();
    ball->SetShape(new Sphere(5));
    ball->SetAppearance(new Material(0x10E050));
    ball_t->AddNode(ball);

    auto cylinder_t = new Transform();
    cylinder_t->Translate(10, 0, -20);
    cylinder_t->Rotate(-90, 1, 0, 0);
    table_top->AddNode(cylinder_t);

    auto cylinder = new Entity();
    cylinder->SetShape(new Cylinder(6, 6, 13));
    cylinder->SetAppearance(new Material(0xF4876A));
    cylinder_t->AddNode(cylinder);

    auto bunny_t = new Transform();
    bunny_t->Translate(10, 20, -20);
//    bunny_t->Translate(0, 7, 0);
    bunny_t->Scale(14, 14, 14);
    table_top->AddNode(bunny_t);

    auto bunny = new Entity();
    bunny->SetAppearance(new Material(0xF03333));
    bunny->SetShape(new Mesh("bunny.off"));
    bunny_t->AddNode(bunny);
}

static Node* CreateTable(float height) {
    const float TABLE_WIDTH = 100.0f;
    const float SURFACE_HEIGHT = 7.0f;
    const float LEG_POSITION = TABLE_WIDTH / 2.0f - 5.0f;

    auto table = new Transform();
    table->Translate(0, -SURFACE_HEIGHT / 2, 0);

    auto leg = new Entity();
    leg->SetShape(new Cylinder(3, 3, height - SURFACE_HEIGHT));
    leg->SetAppearance(new Material(0xD2B48C));

    auto create_leg = [table, leg, SURFACE_HEIGHT] (float x, float z) {
        auto leg_t = new Transform();
        leg_t->Translate(x, -SURFACE_HEIGHT / 2, z);
        leg_t->Rotate(90, 1, 0, 0);
        leg_t->AddNode(leg);
        table->AddNode(leg_t);
    };
    create_leg(LEG_POSITION, LEG_POSITION);
    create_leg(LEG_POSITION, -LEG_POSITION);
    create_leg(-LEG_POSITION, LEG_POSITION);
    create_leg(-LEG_POSITION, -LEG_POSITION);

    auto surface = new Entity();
    surface->SetAppearance(new Texture("wood.png"));
    surface->SetShape(new Cube(TABLE_WIDTH, SURFACE_HEIGHT, TABLE_WIDTH));
    table->AddNode(surface);

    return table;
}

static std::tuple<Node*, Camera*, Manipulator*> CreateLamp() {
    auto lamp = new Transform();
    lamp->Rotate(90, -1, 0, 0);

    const float BASE_RADIUS = 10;
    const float BASE_HEIGHT = 3;
    const float ARM_RADIUS = 1.5;
    const float ARM_HEIGHT = 35;
    const float ARM_OFFSET = 3;
    const float CONE_HEIGHT = 16;

    auto base = new Entity();
    base->SetAppearance(new Material(0x736F66));
    base->SetShape(new Cylinder(BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT));
    lamp->AddNode(base);

    auto arm_s = new Cylinder(ARM_RADIUS, ARM_RADIUS, ARM_HEIGHT);

    auto arm1_t = new Transform();
    arm1_t->Rotate(-25, 1, 0, 0);
    lamp->AddNode(arm1_t);

    auto arm_material = new Material(0xF3F3F3);

    auto arm1 = new Entity();
    arm1->SetAppearance(arm_material);
    arm1->SetShape(arm_s);
    arm1_t->AddNode(arm1);

    auto arm2_t = new Transform();
    arm2_t->Translate(0, 0, ARM_HEIGHT - ARM_OFFSET);
    arm2_t->Rotate(90, 1, 0, 0);
    arm2_t->Translate(0, 0, -ARM_OFFSET);
    arm1_t->AddNode(arm2_t);

    auto arm2 = new Entity();
    arm2->SetAppearance(arm_material);
    arm2->SetShape(arm_s);
    arm2_t->AddNode(arm2);

    auto cone_t = new Transform();
    cone_t->Translate(0, 0, ARM_HEIGHT);
    cone_t->Rotate(90, 1, 0, 0);
    arm2_t->AddNode(cone_t);

    auto cone = new Entity();
    cone->SetShape(new Cylinder(0, CONE_HEIGHT / 2, CONE_HEIGHT, false));
    cone_t->AddNode(cone);

    auto cone_m = new Material(0x22ADC2);
    cone_m->SetShininess(25);
    cone_m->SetSpecular(0.5, 0.5, 0.5);
    cone->SetAppearance(cone_m);

    auto light_t = new Transform();
    light_t->Translate(0, 0, 0);
    cone_t->AddNode(light_t);

    auto light = new Light();
    light->SetupSpot(0, 0, 1, 26.5, 0);
    light_t->AddNode(light);

    auto camera_t = new Transform();
    camera_t->Translate(0, 0, CONE_HEIGHT / 2);
    cone_t->AddNode(camera_t);

    auto camera = new Camera();
    camera->SetEye(0, 0, 0);
    camera->SetCenter(0, 0, 1);
    camera->SetUp(0, 1, 0);
    camera->SetActive(false);
    camera_t->AddNode(camera);

    auto manipulator = new Manipulator();
    manipulator->SetInvertAxis(true);
    cone_t->SetManipulator(manipulator);

    return std::make_tuple(lamp, camera, manipulator);
}

