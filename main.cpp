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
#include "Engine.h"
#include "Light.h"
#include "Manipulator.h"
#include "Mesh.h"
#include "Scene.h"
#include "ToonShaderNode.h"
#include "Transform.h"

/* Scene nodes */
static Scene *scene = nullptr;
static Engine *engine = nullptr;
static Camera *globalcamera = nullptr;
static Camera *jeepcamera = nullptr;
static Manipulator *curr_manipulator = nullptr;
static Manipulator *global_manipulator = nullptr;
static Manipulator *jeep_manipulator = nullptr;

/* Auxiliary functions and glut callbacks */
static void Display();
static void Keyboard(unsigned char key, int x, int y);
static void Idle();
static void Mouse(int button, int state, int x, int y);
static void Motion(int x, int y);
static void CreateScene();
static std::shared_ptr<ToonShaderNode> CreateJeepItem(
        std::shared_ptr<Transform> jeep, const std::string& name,
        unsigned int color);
static std::shared_ptr<Transform> CreateJeep();

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Scene Graph");
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutIdleFunc(Idle);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "GLEW Error: " << glewGetErrorString(err) << "\n";
        exit(1);
    }
    CreateScene();
    glutMainLoop();
    return 0; 
}
    
static void Display() {
    scene->RenderScene();
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
            bool global_active = globalcamera->GetActive();
            globalcamera->SetActive(!global_active);
            jeepcamera->SetActive(global_active);
            if (global_active)
                curr_manipulator = jeep_manipulator;
            else
                curr_manipulator = global_manipulator;
        }
    }
    engine->Keyboard(key);
    glutPostRedisplay();
}

static void Idle() {
    engine->Update();
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

    auto camera = std::make_shared<Camera>();
    globalcamera = camera.get();
//    camera->SetEye(5, 2, 3);
    camera->SetActive(false);
    camera->SetEye(20, 5, 20);
    camera->SetCenter(0.5, 0.5, 0);
    camera->SetUp(0, 1, 0);
    camera->SetPerspective(50, 0.5, 50);
    scene->AddNode(camera);

    global_manipulator = new Manipulator();
    camera->SetManipulator(std::unique_ptr<Manipulator>(global_manipulator));

    auto light = std::make_shared<Light>();
    light->SetPosition(0, 3, 0);
    scene->AddNode(light);

    auto floor_t = std::make_shared<Transform>();
    floor_t->Scale(1000, 0, 1000);
    scene->AddNode(floor_t);

    auto floor = std::make_shared<ToonShaderNode>();
    floor->SetColor(0xBADA5F);
    floor->SetMesh("data/quad.msh");
    floor_t->AddNode(floor);

    auto reference_point_t = std::make_shared<Transform>();
    reference_point_t->Translate(-10, 5, 0);
    reference_point_t->Scale(3, 3, 3);
    reference_point_t->Rotate(90, 0, -1, 0);
    reference_point_t->Rotate(90, -1, 0, 0);
    scene->AddNode(reference_point_t);

    auto reference_point = std::make_shared<ToonShaderNode>(0x150812);
    reference_point->SetMesh("data/klingon_starship.off");
    reference_point_t->AddNode(reference_point);

    auto jeep = CreateJeep();
    scene->AddNode(jeep);
}

static std::shared_ptr<ToonShaderNode> CreateJeepItem(
        std::shared_ptr<Transform> jeep, const std::string& name,
        unsigned int color) {
    auto item = std::make_shared<ToonShaderNode>(color, 0.009);
    item->SetMesh("data/jeep_" + name + ".msh");
    jeep->AddNode(item);
    return item;
}

static std::shared_ptr<Transform> CreateJeep() {
    auto jeep = std::make_shared<Transform>();
    jeep->Rotate(90, -1, 0, 0);

    // Create static stuff
    CreateJeepItem(jeep, "body", 0xD1943F);
    CreateJeepItem(jeep, "lanterns", 0x991111);
    CreateJeepItem(jeep, "handle", 0xAAAAEE);
    CreateJeepItem(jeep, "panel", 0x222222);
    CreateJeepItem(jeep, "seat", 0x705A34);
    CreateJeepItem(jeep, "windshieldcleaner", 0x222222);
//    CreateJeepItem(jeep, "windshield", 0xEEEEEE);

    // Create driver
    auto bunny_t = std::make_shared<Transform>();
    bunny_t->Translate(0.5, -1, 0.9);
    bunny_t->Scale(0.8, 0.8, 0.8);
    bunny_t->Rotate(90, 1, 0, 0);
    bunny_t->Rotate(90, 0, 1, 0);
    jeep->AddNode(bunny_t);

    auto bunny = std::make_shared<ToonShaderNode>();
    bunny->SetColor(0xAA55AA);
    bunny->SetMesh(std::make_shared<Mesh>("data/bunny.msh"));
    bunny_t->AddNode(bunny);

    // Create right wheel
    auto rightwheel = std::make_shared<Transform>();
    rightwheel->Translate(-2.5, 0.644, -0.438);
    auto tire = CreateJeepItem(rightwheel, "tire", 0x444444);
    auto hubcap = CreateJeepItem(rightwheel, "hubcap", 0xAAAAAA);

    // Create front right wheel
    auto frontrightwheel_speed = std::make_shared<Transform>();
    frontrightwheel_speed->AddNode(rightwheel);

    auto frontrightwheel_direction = std::make_shared<Transform>();
    frontrightwheel_direction->AddNode(frontrightwheel_speed);

    auto frontrightwheel = std::make_shared<Transform>();
    frontrightwheel->AddNode(frontrightwheel_direction);
    frontrightwheel->Translate(2.5, -0.644, 0.438);
    jeep->AddNode(frontrightwheel);

    // Create back right wheel
    auto backrightwheel_speed = std::make_shared<Transform>();
    backrightwheel_speed->AddNode(rightwheel);

    auto backrightwheel = std::make_shared<Transform>();
    backrightwheel->AddNode(backrightwheel_speed);
    backrightwheel->Translate(0, -0.644, 0.438);
    jeep->AddNode(backrightwheel);

    // Create left wheel
    auto leftwheel = std::make_shared<Transform>();
    leftwheel->Rotate(180, 0, 0, 1);
    leftwheel->AddNode(rightwheel);

    // Create front left wheel
    auto frontleftwheel_speed = std::make_shared<Transform>();
    frontleftwheel_speed->AddNode(leftwheel);

    auto frontleftwheel_direction = std::make_shared<Transform>();
    frontleftwheel_direction->AddNode(frontleftwheel_speed);

    auto frontleftwheel = std::make_shared<Transform>();
    frontleftwheel->AddNode(frontleftwheel_direction);
    frontleftwheel->Translate(2.5, 0.644, 0.438);
    jeep->AddNode(frontleftwheel);

    // Create back left wheel
    auto backleftwheel_speed = std::make_shared<Transform>();
    backleftwheel_speed->AddNode(leftwheel);

    auto backleftwheel = std::make_shared<Transform>();
    backleftwheel->AddNode(backleftwheel_speed);
    backleftwheel->Translate(0, 0.644, 0.438);
    jeep->AddNode(backleftwheel);

    // Create lights
    auto rightlight = CreateJeepItem(jeep, "light", 0xEEEEEE);

    auto leftlight = std::make_shared<Transform>();
    leftlight->Translate(0, 1.028, 0);
    leftlight->AddNode(rightlight);
    jeep->AddNode(leftlight);

    // Create steering wheel
    auto steering_wheel_centered = std::make_shared<Transform>();
    steering_wheel_centered->Translate(-1.111, -0.495, -1.372);
    CreateJeepItem(steering_wheel_centered, "steeringwheel", 0x222222);

    auto steering_wheel_engine = std::make_shared<Transform>();
    steering_wheel_engine->AddNode(steering_wheel_centered);

    auto steering_wheel = std::make_shared<Transform>();
    steering_wheel->AddNode(steering_wheel_engine);
    steering_wheel->Translate(1.111, 0.495, 1.372);
    jeep->AddNode(steering_wheel);

    // Creates the engine
    engine = new Engine(jeep, frontleftwheel_direction,
            frontrightwheel_direction, frontleftwheel_speed,
            frontrightwheel_speed, backleftwheel_speed, backrightwheel_speed,
            steering_wheel_engine);

    // Creates the camera
    auto jeepcamera_t = std::make_shared<Transform>();
    curr_manipulator = jeep_manipulator = new Manipulator();
    jeepcamera_t->SetManipulator(
            std::unique_ptr<Manipulator>(jeep_manipulator));
    jeepcamera_t->Translate(0.6, 0.5, 1.7);
    jeep->AddNode(jeepcamera_t);

    auto camera = std::make_shared<Camera>();
    jeepcamera = camera.get();
    camera->SetEye(0, 0, 0);
    camera->SetCenter(1, 0, 0);
    camera->SetUp(0, 0, 1);
    camera->SetPerspective(50, 0.5, 50);
    jeepcamera_t->AddNode(camera);

    return jeep;
}

