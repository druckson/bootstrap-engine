#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <iostream>
#include <unordered_map>
#include "../engine/System.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;

class Graphics : public System {
    GLFWwindow* _window;
    GLuint *_vbos;
    //std::unordered_map<Entity, GraphicsObject *> _entities;
public:
    Graphics();
    ~Graphics();
    void Init();
    void AddEntity(Entity entity, void *data);
    void Update(float dt);
    void Draw();
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
    this->_window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

    if (!this->_window) {
        cerr << "ERROR: Failed to set up GLFW window" << endl;    
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(this->_window);
    glewInit();

    //float vertices[] = {
    //     0.5f, -0.5, 0.0,
    //    -0.5f, -0.5, 0.0,
    //    -0.5f,  0.5, 0.0,
    //     0.5f, -0.5, 0.0,
    //    -0.5f,  0.5, 0.0,
    //     0.5f,  0.5, 0.0
    //};

    float vertices[] = {
        -0.6f, -0.4f, 0.f,
        0.6f, -0.4f, 0.f,
        0.f, 0.6f, 0.f
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
      
    int width, height;
    glfwGetFramebufferSize(this->_window, &width, &height);
    glViewport(0, 0, width, height);

    this->_vbos = new GLuint[3];
    glGenBuffers(3, this->_vbos);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    return;
}

void Graphics::AddEntity(Entity entity, void *data) {
    return;
}

void Graphics::Update(float dt) {
    return;
}

void Graphics::Draw() {
    if (glfwWindowShouldClose(this->_window))
        glfwDestroyWindow(this->_window);
    else {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(this->_window, &width, &height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        ratio = width / (float) height;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[0]);
        glVertexPointer(3, GL_FLOAT, 3*sizeof(float), 0);

        glEnableClientState(GL_COLOR_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[1]);
        glColorPointer(3, GL_FLOAT, 3*sizeof(float), 0);

        glDrawArrays(GL_TRIANGLES,0,3);
        glFlush();  

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }
    return;
}

void Graphics::RemoveEntity(Entity entity) {
    return;
}

#endif
