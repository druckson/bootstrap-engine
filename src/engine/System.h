#ifndef SYSTEM_H
#define SYSTEM_H
#include "Entity.h"

class System {
public:
    virtual void Init() {}
    virtual void AddEntity(Entity entity, void *data) {}
    virtual void Update(float dt) {}
    virtual void Draw() {}
    virtual void RemoveEntity(Entity entity) {}
};

#endif
