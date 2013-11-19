#ifndef PHYSICS_H
#define PHYSICS_H
#include <iostream>
#include <unordered_map>
#include "../engine/System.h"
using namespace std;

class PhysicsObject {
    
};

class Physics : public System {
    std::unordered_map<Entity, PhysicsObject *> _entities;
public:
    Physics();
    ~Physics();
    void Init();
    void AddEntity(Entity entity, void *data);
    void Update(float dt);
    void RemoveEntity(Entity entity);
};

Physics::Physics() {

}

void Physics::Init() {
    return;
}

void Physics::AddEntity(Entity entity, void *data) {
    return;
}

void Physics::Update(float dt) {
    return;
}

void Physics::RemoveEntity(Entity entity) {
    return;
}

#endif
