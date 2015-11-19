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
static Transform *sun = nullptr;
static float sun_alpha = 0;
static Light *jeep_light = nullptr;
static const char *kKeyboardCommands =
"Keys:\n"
"        q       Quit\n"
"        c       Change camera\n"
"        wasd    Control jeep\n"
"        space   Jeep break\n"
"        l       Toggle jeep lights\n"
"        b       Toggle sun light\n"
"        nm      Rotate sun\n";

/* Auxiliary functions and glut callbacks */
static void Display();
static void Keyboard(unsigned char key, int x, int y);
static void Idle();
static void Mouse(int button, int state, int x, int y);
static void Motion(int x, int y);
static void CreateScene();
static std::shared_ptr<Camera> CreateCamera(Group *parent, int cameraId);
static std::shared_ptr<Transform> CreateSun();
static std::shared_ptr<Transform> CreateRoad();
static std::shared_ptr<Transform> CreateShip();
static std::shared_ptr<ToonShaderNode> CreateJeepItem(
        std::shared_ptr<Transform> jeep, const std::string& name,
        unsigned int color);
static std::shared_ptr<Transform> CreateJeep();

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | 
            GLUT_MULTISAMPLE);
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
    std::cout << kKeyboardCommands;
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
            exit(0);
            break;
        case 'b':
            sun->SetActive(!sun->GetActive());
            if (sun->GetActive())
                scene->SetBackgroud(0.69, 0.95, 1.00);
            else
                scene->SetBackgroud(0.17, 0.21, 0.29);
            break;
        case 'l':
            jeep_light->SetActive(!jeep_light->GetActive());
            break;
        case 'c':
            cameras[curr_camera].camera->SetActive(false);
            curr_camera = (curr_camera + 1) % kNCameras;
            cameras[curr_camera].camera->SetActive(true);
            break;
        case 'n':
        case 'm': {
            float alpha = 2.5 * (key == 'n' ? 1 : -1);
            if (fabs(sun_alpha + alpha) < 60) {
                sun_alpha += alpha;
                sun->Rotate(alpha, 1, 0, 0);
            }
            break;
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
    cameras[curr_camera].manipulator->GlutMouse(button, state, x, y);
    glutPostRedisplay();
}

static void Motion(int x, int y) {
    cameras[curr_camera].manipulator->GlutMotion(x, y);
    glutPostRedisplay();
}

static void CreateScene() {
    scene = new Scene();
    scene->SetBackgroud(0.69, 0.95, 1.00);

    auto camera = CreateCamera(scene, kGlobal);
    camera->SetEye(20, 5, 20);
    camera->SetCenter(0.5, 0.5, 0);
    camera->SetUp(0, 1, 0);

    scene->AddNode(CreateSun());
    scene->AddNode(CreateRoad());
    scene->AddNode(CreateShip());
    scene->AddNode(CreateJeep());
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

static std::shared_ptr<Transform> CreateSun() {
    sun = new Transform();

    auto sun_height = std::make_shared<Transform>();
    sun_height->Translate(0, 100, 0);
    sun->AddNode(sun_height);

    auto light = std::make_shared<Light>();
    light->SetPosition(0, 0, 0);
    light->SetDiffuse(0.5, 0.5, 0.5);
    light->SetAmbient(0.4, 0.4, 0.4);
    light->EnableShadowMap(glm::vec3(0, -1, 0), glm::vec3(1, 0, 0), 100,
            80, 120);
    sun_height->AddNode(light);

    return std::shared_ptr<Transform>(sun);
}

static std::shared_ptr<Transform> CreateRoad() {
    auto floor = std::make_shared<Transform>();

    auto quad = std::make_shared<Mesh>("data/quad.msh");

    auto grass_t = std::make_shared<Transform>();
    grass_t->Scale(1000, 0, 1000);
    floor->AddNode(grass_t);

    auto grass = std::make_shared<ToonShaderNode>(0xBADA5F);
    grass->SetMesh(quad);
    grass_t->AddNode(grass);

    auto road_t = std::make_shared<Transform>();
    road_t->Scale(1000, 1, 10);
    road_t->Translate(0, 0.001, 0);
    floor->AddNode(road_t);

    auto road = std::make_shared<ToonShaderNode>(0x111111);
    road->SetMesh(quad);
    road_t->AddNode(road);

    auto strip = std::make_shared<ToonShaderNode>(0xEEEE11);
    strip->SetMesh(quad);

    for (int i = 0; i < 125; ++i) {
        auto strip_t = std::make_shared<Transform>();
        strip_t->Translate(i * 8 - 500, 0.002, 0);
        strip_t->Scale(2.5, 1, 0.2);
        strip_t->AddNode(strip);
        floor->AddNode(strip_t);
    }

    return floor;
}

static std::shared_ptr<Transform> CreateShip() {
    auto ship_t = std::make_shared<Transform>();
    ship_t->Translate(-10, 5, 0);
    ship_t->Scale(3, 3, 3);
    ship_t->Rotate(90, 0, -1, 0);
    ship_t->Rotate(90, -1, 0, 0);

    auto ship = std::make_shared<ToonShaderNode>(0x444444);
    ship->SetMesh("data/klingon_starship.off");
    ship_t->AddNode(ship);

    return ship_t;
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
    auto windshield = CreateJeepItem(jeep, "windshield", 0xBBBBEE);
    windshield->SetOpacity(0.3);

    // Create driver
    auto bunny_t = std::make_shared<Transform>();
    bunny_t->Translate(0.9, -0.6, 1.2);
    bunny_t->Scale(0.6, 0.6, 0.6);
    bunny_t->Rotate(90, 1, 0, 0);
    bunny_t->Rotate(90, 0, 1, 0);
    jeep->AddNode(bunny_t);

    auto bunny = std::make_shared<ToonShaderNode>(0xAA55AA, 0.02);
    bunny->SetMesh(std::make_shared<Mesh>("data/bunny.off"));
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
    auto rightlight_model = CreateJeepItem(rightlight, "light", 0xEEEEEE);
    rightlight_model->SetOpacity(0.3);
    jeep->AddNode(rightlight);

    auto rightlight_spot = std::make_shared<Light>();
    rightlight_spot->SetActive(false);
    rightlight_spot->SetPosition(2.956, -0.514, 1.074);
    rightlight_spot->SetupSpot(1, 0, -0.1, 45, 16);
    rightlight_spot->SetDiffuse(0, 0, 0);
    rightlight_spot->SetAmbient(0.42, 0.42, 0.42);
    rightlight_spot->SetAttenuation(1, 0.002, 0);
    rightlight->AddNode(rightlight_spot);
    jeep_light = rightlight_spot.get();

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
    jeepcamera->SetEye(-6, 2, 0);
    jeepcamera->SetCenter(1, 1, 0);
    jeepcamera->SetUp(0, 1, 0);

    return jeep;
}

