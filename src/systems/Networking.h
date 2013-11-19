#ifndef PHYSICS_H
#define PHYSICS_H
#include <iostream>
#include <unordered_map>
#include "../engine/System.h"
#include <enet/enet.h>
using namespace std;

class Networking : public System {
    std::unordered_map<Entity, NetworkingObject *> _entities;
public:
    Networking();
    ~Networking();
    void Init();
    void AddEntity(Entity entity, void *data);
    void Update(float dt);
    void RemoveEntity(Entity entity);
};

Networking::Networking() {
    if (!enet_initialize()) {
        cerr << "Failed to set up enet" << endl;
    }
}

Networking::~Networking() {
    enet_deinitialize();
}

void Networking::Init() {
    return;
}

void Networking::AddEntity(Entity entity, void *data) {
    return;
}

void Networking::Update(float dt) {
    return;
}

void Networking::RemoveEntity(Entity entity) {
    return;
}

#endif
