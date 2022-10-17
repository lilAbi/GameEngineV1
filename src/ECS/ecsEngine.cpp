#include "ecsEngine.h"

void ECS::EcsEngine::Update(float deltaTime) {
    systemManager.Update(deltaTime);
    //dispatch events
}

void ECS::EcsEngine::StartUp() {
    systemManager.StartUpSystems();
}
