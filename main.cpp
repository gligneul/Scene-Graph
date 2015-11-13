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

/* Scene and engine*/
static Scene *scene = nullptr;
static Engine *engine = nullptr;

/* Cameras and manipulators */
enum CameraList {
    kGlobal,
    kDriver,
    kJeep,
    kNCameras
};
static struct {
    Camera *camera;
    Manipulator *manipulator;
} cameras[kNCameras];
static int curr_camera = kDriver;

/* Other stuff */
static Light *sun;
static Light *light;

/* Auxiliary functions and glut callbacks */
static void Display();
static void Keyboard(unsigned char key, int x, int y);
static void Idle();
static void Mouse(int button, int state, int x, int y);
static void Motion(int x, int y);
static void CreateScene();
static std::shared_ptr<Camera> CreateCamera(Group *parent, int cameraId);
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
        case 'q':
            delete scene;
            exit(0);
            break;
        case 'l':
            sun->SetActive(!sun->GetActive());
            light->SetActive(!light->GetActive());
            break;
        case 'c':
            cameras[curr_camera].camera->SetActive(false);
            curr_camera = (curr_camera + 1) % kNCameras;
            cameras[curr_camera].camera->SetActive(true);
            break;
    }
    engine->Keyboard(key);
    glutPostRedisplay();
}

static void Idle() {
    engine->Update();
    glutPostRedisplay();
}

static void Mouse(int button, int state, int x, int y) {
    cameras[curr_camera].manipulator->GlutMouse(button, state, x, y);
    glutPostRedisplay();
}

static void Motion(int x, int y) {
    cameras[curr_camera].manipulator->GlutMotion(x, y);
    glutPostRedisplay();
}

static void CreateScene() {
    scene = new Scene();

    auto camera = CreateCamera(scene, kGlobal);
    camera->SetEye(20, 5, 20);
    camera->SetCenter(0.5, 0.5, 0);
    camera->SetUp(0, 1, 0);

    auto light = std::make_shared<Light>();
    light->SetPosition(0, 1, 0, 0.001);
    light->SetDiffuse(0.6, 0.6, 0.6);
    light->SetAmbient(0.4, 0.4, 0.4);
    scene->AddNode(light);
    sun = light.get();

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

static std::shared_ptr<Camera> CreateCamera(Group *parent, int cameraId) {
    auto camera = std::make_shared<Camera>();
    camera->SetPerspective(40, 0.5, 50);
    camera->SetActive(false);
    parent->AddNode(camera);
    auto manipulator = new Manipulator();
    camera->SetManipulator(std::unique_ptr<Manipulator>(manipulator));

    cameras[cameraId].camera = camera.get();
    cameras[cameraId].manipulator = manipulator;

    return camera;
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
    auto rightlight = std::make_shared<Transform>();
    jeep->AddNode(rightlight);
    CreateJeepItem(rightlight, "light", 0xEEEEEE);

    auto rightlight_spot = std::make_shared<Light>();
    rightlight_spot->SetActive(false);
    rightlight_spot->SetPosition(2.956, -0.514, 1.074);
    rightlight_spot->SetupSpot(1, 0, -0.1, 45, 16);
    rightlight_spot->SetDiffuse(0, 0, 0);
    rightlight_spot->SetAmbient(0.42, 0.42, 0.42);
    rightlight_spot->SetAttenuation(1, 0.002, 0);
    rightlight->AddNode(rightlight_spot);
    light = rightlight_spot.get();

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

    // Creates the driver camera
    auto drivercamera_t = std::make_shared<Transform>();
    drivercamera_t->Translate(0.6, 0.5, 1.7);
    drivercamera_t->Rotate(90, 1, 0, 0);
    jeep->AddNode(drivercamera_t);

    auto drivercamera = CreateCamera(drivercamera_t.get(), kDriver);
    drivercamera->SetActive(true);
    drivercamera->SetEye(0, 0, 0);
    drivercamera->SetCenter(1, 0, 0);
    drivercamera->SetUp(0, 1, 0);

    // Creates the 3rd person camera
    auto jeepcamera_t = std::make_shared<Transform>();
    jeepcamera_t->Rotate(90, 1, 0, 0);
    jeep->AddNode(jeepcamera_t);

    auto jeepcamera = CreateCamera(jeepcamera_t.get(), kJeep);
    cameras[kJeep].manipulator->SetReferencePoint(1, 1, 0);
    jeepcamera->SetEye(-4, 1, 0);
    jeepcamera->SetCenter(1, 1, 0);
    jeepcamera->SetUp(0, 1, 0);

    return jeep;
}

