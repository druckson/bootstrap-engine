#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <iostream>
#include <unordered_map>
#include "../engine/System.h"
#include "GLFW/glfw3.h"
using namespace std;

class Graphics : public System {
    GLFWwindow* window;
    //std::unordered_map<Entity, GraphicsObject *> _entities;
public:
    Graphics();
    ~Graphics();
    void Init();
    void AddEntity(Entity entity, void *data);
    void Update(float dt);
    void RemoveEntity(Entity entity);
};

Graphics::Graphics() {
    if (!glfwInit()) {
        cerr << "ERROR: Failed to initialize GLFW" << endl;    
        exit(-1);
    }
}

Graphics::~Graphics() {
    glfwTerminate();    
}

void Graphics::Init() {
    this->window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

    if (!window) {
        cerr << "ERROR: Failed to set up GLFW window" << endl;    
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    return;
}

void Graphics::AddEntity(Entity entity, void *data) {
    return;
}

void Graphics::Update(float dt) {
    cout << "Graphics" << endl;


    return;
}

void Graphics::RemoveEntity(Entity entity) {
    return;
}

#endif
