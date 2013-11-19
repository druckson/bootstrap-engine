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

struct GraphicsObject {
    GLuint vbos[3];
    GLuint shaderProgram;
    double position[3];
};

class Graphics : public System {
    GLFWwindow* _window;
    GLuint *_vbos;
    std::unordered_map<Entity, GraphicsObject *> _entities;
    std::unordered_map<string, GLuint> _shaders;
    GLuint _createVertexShader(const string shaderFile);
    GLuint _createFragmentShader(const string shaderFile);
    GLuint _createShaderProgram(const string vertexShaderFile, const string fragmentShaderFile);
public:
    Graphics();
    ~Graphics();
    void Init();
    void AddEntity(Entity entity, void *data);
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
      
    int width, height;
    glfwGetFramebufferSize(this->_window, &width, &height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glScaled(50./(double)width, 50./(double)height, 1.);
}

GLuint Graphics::_createVertexShader(const string shaderFile) {
    const char *cShaderFile = shaderFile.c_str();
    const GLint len = shaderFile.length();
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &cShaderFile, &len);

    // Print Errors
    GLint error;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
    //cout << "Error: " << error << endl;
}

GLuint Graphics::_createFragmentShader(const string shaderFile) {
    const char *cShaderFile = shaderFile.c_str();
    const GLint len = shaderFile.length();
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &cShaderFile, &len);

    // Print Errors
    GLint error;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
    //cout << "Error: " << error << endl;
}

GLuint Graphics::_createShaderProgram(const string vertexShaderFile, const string fragmentShaderFile) {
    GLuint vertexShader = this->_createVertexShader(vertexShaderFile);
    GLuint fragmentShader = this->_createFragmentShader(fragmentShaderFile);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    return program;
}

void Graphics::AddEntity(Entity entity, void *data) {
    GraphicsObject *obj = new GraphicsObject;

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

    glGenBuffers(3, obj->vbos);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    obj->position[0] = (double)((rand() % 40) - 20.);
    obj->position[1] = (double)((rand() % 40) - 20.);
    obj->position[2] = (double)((rand() % 40) - 20.);

    obj->shaderProgram = this->_createShaderProgram("", "");

    this->_entities[entity] = obj;
}

void Graphics::RemoveEntity(Entity entity) {}

void Graphics::Draw() {
    if (glfwWindowShouldClose(this->_window))
        glfwDestroyWindow(this->_window);
    else {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        for (auto &item: this->_entities) {
            glPushMatrix();
                glTranslated(item.second->position[0], 
                             item.second->position[1], 
                             item.second->position[2]);
                glEnableClientState(GL_VERTEX_ARRAY);
                glBindBuffer(GL_ARRAY_BUFFER, item.second->vbos[0]);
                glVertexPointer(3, GL_FLOAT, 3*sizeof(float), 0);

                glEnableClientState(GL_COLOR_ARRAY);
                glBindBuffer(GL_ARRAY_BUFFER, item.second->vbos[1]);
                glColorPointer(3, GL_FLOAT, 3*sizeof(float), 0);

                glDrawArrays(GL_TRIANGLES,0,3);
            glPopMatrix();
        }
        glFlush();  

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }
    return;
}

#endif
