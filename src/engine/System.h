#ifndef SYSTEM_H
#define SYSTEM_H
#include "Entity.h"

class System {
public:
    virtual void Init();
    virtual void AddEntity(Entity entity, void *data);
    virtual void Update(float dt);
    virtual void RemoveEntity(Entity entity);
};

void System::Init() {}
void System::AddEntity(Entity entity, void *data) {}
void System::Update(float dt) {}
void System::RemoveEntity(Entity entity) {}

#endif
