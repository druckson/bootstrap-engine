#include <iostream>
#include "systems/Physics.h"
#include "systems/Graphics.h"
#include "engine/Engine.h"

using namespace std;

int main(int argc, char **argv) {
    Engine *engine = new Engine();

    engine->AddSystem(new Physics());
    engine->AddSystem(new Graphics());

    for (int i=0; i<150000; i++) {
        Entity e1 = engine->CreateEntity();
    }

    engine->MainLoop();
}
