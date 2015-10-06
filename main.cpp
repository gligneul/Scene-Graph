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

/* Controls */
const char* kControlsStr = 
"Key bindings:\n"
" q - Quit\n"
" c - Switch between global and lamp camera\n"
" m - Switch between global and lamp manipulator\n"
" f - Switch between fog types\n";

/* Scene nodes */
static Scene* scene = nullptr;
static Environ* environ = nullptr;
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
static std::shared_ptr<Node> CreateTable(float height);
static std::tuple<std::shared_ptr<Node>, std::shared_ptr<Camera>, Manipulator*>
        CreateLamp();

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
    std::cout << kControlsStr;
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
        case 'c': {
            bool is_global_active = global_camera->GetActive();
            global_camera->SetActive(!is_global_active);
            lamp_camera->SetActive(is_global_active);
            if (is_global_active)
                curr_manipulator = lamp_manipulator;
            else
                curr_manipulator = global_manipulator;
            break;
        }
        case 'm': {
            if (curr_manipulator == global_manipulator)
                curr_manipulator = lamp_manipulator;
            else
                curr_manipulator = global_manipulator;
            break;
        }
        case 'f': {
            environ->SwitchFog();
            break;
        }
    }
    glutPostRedisplay();
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

    environ = new Environ();
    environ->SetBackgroundColor(0xC5E0ED);
    environ->SetAmbient(0.2, 0.2, 0.2);
    environ->SetFogColor(0xC5E0ED);
    environ->SetLinearFog(200, 500);
    environ->SetExponentialFog(0.003);
    scene->SetEnviron(std::unique_ptr<Environ>(environ));

    auto global_camera_ptr = std::make_shared<Camera>();
    global_camera = global_camera_ptr.get();
    global_camera->SetEye(130, 200, 130);
    global_camera->SetCenter(0, 100, 0);
    global_camera->SetPerspective(50, 5, 500);
    scene->AddNode(global_camera_ptr);

    curr_manipulator = global_manipulator = new Manipulator();
    global_manipulator->SetReferencePoint(0, 100, 0);
    global_camera->SetManipular(
            std::unique_ptr<Manipulator>(global_manipulator));

    auto light_t = std::make_shared<Transform>();
    light_t->Translate(0, 200, 0);
    scene->AddNode(light_t);

    auto light = std::make_shared<Light>();
    light_t->AddNode(light);

    auto light_sphere = std::make_shared<Entity>();
    light_sphere->SetAppearance(std::make_shared<Material>(0xFFFFFF));
    light_sphere->SetShape(std::make_shared<Sphere>(3));
    light_t->AddNode(light_sphere);

    auto floor = std::make_shared<Entity>();
    floor->SetAppearance(std::make_shared<Material>(0xBADA5F));
    floor->SetShape(std::make_shared<Cube>(500, 0.1, 500));
    scene->AddNode(floor);

    static const float TABLE_HEIGHT = 100;
    auto table_top = std::make_shared<Transform>();
    table_top->Translate(0, TABLE_HEIGHT, 0);
    scene->AddNode(table_top);

    auto table = CreateTable(TABLE_HEIGHT);
    table_top->AddNode(table);

    auto lamp_t = std::make_shared<Transform>();
    lamp_t->Translate(-30, 0, 30);
    lamp_t->Rotate(135, 0, 1, 0);
    table_top->AddNode(lamp_t);

    auto lamp = CreateLamp();
    lamp_t->AddNode(std::get<0>(lamp));
    lamp_camera = std::get<1>(lamp).get();
    lamp_manipulator = std::get<2>(lamp);

    auto ball_t = std::make_shared<Transform>();
    ball_t->Translate(15, 5, 15);
    table_top->AddNode(ball_t);

    auto ball = std::make_shared<Entity>();
    ball->SetShape(std::make_shared<Sphere>(5));
    ball->SetAppearance(std::make_shared<Material>(0x10E050));
    ball_t->AddNode(ball);

    auto cylinder_t = std::make_shared<Transform>();
    cylinder_t->Translate(10, 0, -20);
    cylinder_t->Rotate(-90, 1, 0, 0);
    table_top->AddNode(cylinder_t);

    auto cylinder = std::make_shared<Entity>();
    cylinder->SetShape(std::make_shared<Cylinder>(6, 6, 13));
    cylinder->SetAppearance(std::make_shared<Material>(0xF4876A));
    cylinder_t->AddNode(cylinder);

    auto bunny_t = std::make_shared<Transform>();
    bunny_t->Translate(10, 20, -20);
    bunny_t->Scale(14, 14, 14);
    table_top->AddNode(bunny_t);

    auto bunny = std::make_shared<Entity>();
    bunny->SetAppearance(std::make_shared<Material>(0xF6F6E2));
    bunny->SetShape(std::make_shared<Mesh>("bunny.off"));
    bunny_t->AddNode(bunny);
}

static std::shared_ptr<Node> CreateTable(float height) {
    const float TABLE_WIDTH = 100.0f;
    const float SURFACE_HEIGHT = 7.0f;
    const float LEG_POSITION = TABLE_WIDTH / 2.0f - 5.0f;

    auto table = std::make_shared<Transform>();
    table->Translate(0, -SURFACE_HEIGHT / 2, 0);

    auto leg = std::make_shared<Entity>();
    leg->SetShape(std::make_shared<Cylinder>(3, 3, height - SURFACE_HEIGHT));
    leg->SetAppearance(std::make_shared<Material>(0xD2B48C));

    auto create_leg = [table, leg, SURFACE_HEIGHT] (float x, float z) {
        auto leg_t = std::make_shared<Transform>();
        leg_t->Translate(x, -SURFACE_HEIGHT / 2, z);
        leg_t->Rotate(90, 1, 0, 0);
        leg_t->AddNode(leg);
        table->AddNode(leg_t);
    };
    create_leg(LEG_POSITION, LEG_POSITION);
    create_leg(LEG_POSITION, -LEG_POSITION);
    create_leg(-LEG_POSITION, LEG_POSITION);
    create_leg(-LEG_POSITION, -LEG_POSITION);

    auto surface = std::make_shared<Entity>();
    surface->SetAppearance(std::make_shared<Texture>("wood.png"));
    surface->SetShape(
            std::make_shared<Cube>(TABLE_WIDTH, SURFACE_HEIGHT, TABLE_WIDTH));
    table->AddNode(surface);

    return table;
}

std::tuple<std::shared_ptr<Node>, std::shared_ptr<Camera>, Manipulator*>
        CreateLamp() {
    auto lamp = std::make_shared<Transform>();
    lamp->Rotate(90, -1, 0, 0);

    const float BASE_RADIUS = 10;
    const float BASE_HEIGHT = 3;
    const float ARM_RADIUS = 1.5;
    const float ARM_HEIGHT = 35;
    const float ARM_OFFSET = 3;
    const float CONE_HEIGHT = 16;

    auto base = std::make_shared<Entity>();
    base->SetAppearance(std::make_shared<Material>(0x736F66));
    base->SetShape(
            std::make_shared<Cylinder>(BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT));
    lamp->AddNode(base);

    auto arm_s = std::make_shared<Cylinder>(ARM_RADIUS, ARM_RADIUS, ARM_HEIGHT);

    auto arm1_t = std::make_shared<Transform>();
    arm1_t->Rotate(-25, 1, 0, 0);
    lamp->AddNode(arm1_t);

    auto arm_material = std::make_shared<Material>(0xF3F3F3);

    auto arm1 = std::make_shared<Entity>();
    arm1->SetAppearance(arm_material);
    arm1->SetShape(arm_s);
    arm1_t->AddNode(arm1);

    auto arm2_t = std::make_shared<Transform>();
    arm2_t->Translate(0, 0, ARM_HEIGHT - ARM_OFFSET);
    arm2_t->Rotate(90, 1, 0, 0);
    arm2_t->Translate(0, 0, -ARM_OFFSET);
    arm1_t->AddNode(arm2_t);

    auto arm2 = std::make_shared<Entity>();
    arm2->SetAppearance(arm_material);
    arm2->SetShape(arm_s);
    arm2_t->AddNode(arm2);

    auto cone_t = std::make_shared<Transform>();
    cone_t->Translate(0, 0, ARM_HEIGHT);
    cone_t->Rotate(90, 1, 0, 0);
    arm2_t->AddNode(cone_t);

    auto cone = std::make_shared<Entity>();
    cone->SetShape(
            std::make_shared<Cylinder>(0, CONE_HEIGHT / 2, CONE_HEIGHT, false));
    cone_t->AddNode(cone);

    auto cone_m = std::make_shared<Material>(0x22ADC2);
    cone_m->SetShininess(25);
    cone_m->SetSpecular(0.5, 0.5, 0.5);
    cone->SetAppearance(cone_m);

    auto light_t = std::make_shared<Transform>();
    light_t->Translate(0, 0, 0);
    cone_t->AddNode(light_t);

    auto light = std::make_shared<Light>();
    light->SetupSpot(0, 0, 1, 26.5, 64);
    light_t->AddNode(light);

    auto camera_t = std::make_shared<Transform>();
    camera_t->Translate(0, 0, CONE_HEIGHT / 2);
    cone_t->AddNode(camera_t);

    auto camera = std::make_shared<Camera>();
    camera->SetEye(0, 0, 0);
    camera->SetCenter(0, 0, 1);
    camera->SetUp(0, 1, 0);
    camera->SetActive(false);
    camera_t->AddNode(camera);

    auto manipulator = new Manipulator();
    manipulator->SetInvertAxis(true);
    cone_t->SetManipulator(std::unique_ptr<Manipulator>(manipulator));

    return std::make_tuple(lamp, camera, manipulator);
}

