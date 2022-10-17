#include "API.h"


namespace ECS{
    ECS::EcsEngine* ecsEngine = nullptr;

    ECS::EcsEngine* Initialize(){
        if(!ecsEngine)
            ecsEngine = new ECS::EcsEngine();
        return ecsEngine;
    }

    void Destroy(){
        delete ecsEngine;
    }
}