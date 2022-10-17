
#include "systemManager.h"

void SystemManager::Update(float deltaTime) {

    //pre update
    for(const auto& systemPtr: systemExecuteOrder){

        if(systemPtr->needUpdate && systemPtr->systemEnabled){
            systemPtr->PreUpdate(deltaTime);
        }

    }

    //normal update
    for(const auto& systemPtr: systemExecuteOrder){

        if(systemPtr->needUpdate && systemPtr->systemEnabled){
            systemPtr->Update(deltaTime);
        }

    }

    //post update
    for(const auto& systemPtr: systemExecuteOrder){

        if(systemPtr->needUpdate && systemPtr->systemEnabled){
            systemPtr->PostUpdate(deltaTime);
        }

    }

}

void SystemManager::StartUpSystems() {
    //initalizes all the systems
    for(const auto& systemPtr: systemExecuteOrder){
        if(systemPtr->needUpdate && systemPtr->systemEnabled){
            systemPtr->Init();
        }
    }

}

