#ifndef PHYSICS_H
#define PHYSICS_H
#include <iostream>
#include <unordered_map>
#include "../engine/System.h"
using namespace std;

class Input : public System {
    std::unordered_map<Entity, InputObject *> _entities;
public:
    Input();
    ~Input();
    void Init();
    void AddEntity(Entity entity, void *data);
    void Update(float dt);
    void RemoveEntity(Entity entity);
};

Input::Input() {

}

void Input::Init() {
    return;
}

void Input::AddEntity(Entity entity, void *data) {
    return;
}

void Input::Update(float dt) {
    return;
}

void Input::RemoveEntity(Entity entity) {
    return;
}

#endif
