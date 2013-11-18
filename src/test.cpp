#include <iostream>
#include "systems/Physics.h"
#include "systems/Graphics.h"
#include "engine/Engine.h"

using namespace std;

int main(int argc, char **argv) {
    Engine *engine = new Engine();

    engine->AddSystem(new Physics());
    engine->AddSystem(new Graphics());

    Entity e1 = engine->CreateEntity();
    Entity e2 = engine->CreateEntity();
    Entity e3 = engine->CreateEntity();

    engine->MainLoop();

    std::cout << "Hello World! " << e1 << e2 << e3 << std::endl;
}
