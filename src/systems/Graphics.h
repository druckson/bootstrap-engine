#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "../engine/System.h"
#include <iostream>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
using namespace std;

struct Sprite {
    int index;
    float position[2];
};

class Graphics : public System {
    GLFWwindow* _window;
    int _currentIndex;
    GLuint _shaderProgram;
    GLuint _vbos[3];
    float _vertices[16000*6];
    unordered_map<Entity, Sprite *> _entities;
    unordered_map<string, GLuint> _shaders;
public:
    Graphics();
    ~Graphics();
    void Init();
    void AddEntity(Entity entity, void *data);
    void Update(float dt);
    void Draw();
    void RemoveEntity(Entity entity);
};
#endif
