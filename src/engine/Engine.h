#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "Entity.h"
#include "System.h"
#include <unordered_set>
#include <chrono>
#include <boost/thread/thread.hpp>

using namespace std;

class Engine {
    Entity _nextEntity;
    unordered_set<Entity> _entities;
    unordered_set<System *> _systems;
    bool _run;
    int _frameRate;
public:
    Engine();
    void AddSystem(System *system);
    void Update(float dt);
    void MainLoop();
    Entity CreateEntity();
};

Engine::Engine() {
    this->_nextEntity = 0;
    this->_run = true;
    this->_frameRate = 60;
}

void Engine::AddSystem(System *system) {
    this->_systems.insert(system);
}

void Engine::Update(float dt) {
    for (const auto& system: this->_systems) {
        system->Update(dt);
    }
}

void Engine::MainLoop() {
    double dt;
    auto then = chrono::high_resolution_clock::now();
    while (this->_run) {
        auto now = chrono::high_resolution_clock::now();

        dt = (double)(chrono::duration_cast<chrono::microseconds>(now - then).count()) / 1000000.0;
        this->Update(dt);
        then = now;
        boost::this_thread::sleep(boost::posix_time::microseconds(1000000.0 / (double)this->_frameRate));
    }
}

Entity Engine::CreateEntity() {
    Entity newEntity = this->_nextEntity++;
    this->_entities.insert(newEntity);
    return newEntity;
}
#endif