#ifndef BLOCKRPG_GAMEENGINE_H
#define BLOCKRPG_GAMEENGINE_H

#include <chrono>
#include <memory>

#include "ECS/API.h"
#include "GameEngine/Core/Core.h"
#include "GameEngine/Component/componentList.h"
#include "GameEngine/System/systemList.h"

//manages the entire game
class GameEngine {
public:
    GameEngine()    = default;
    ~GameEngine()   = default;

    //initialize archetypes
    void Init();

    //set up systems/entites
    void Setup();

    //run the ECS engine
    void Run();

public:
    Window window{};
    ECS::EcsEngine* ecsEngine{nullptr};
};


#endif //BLOCKRPG_GAMEENGINE_H
