
#ifndef BLOCKRPG_ECSENGINE_H
#define BLOCKRPG_ECSENGINE_H

#include "ECS/Managers/componentManager.h"
#include "ECS/Managers/entityManager.h"
#include "ECS/Managers/systemManager.h"

namespace ECS {

    //manages the ECS architecture- Singleton
    class EcsEngine {
    public:
        EcsEngine() = default;
        ~EcsEngine() = default;

        //tick ECS engine
        void Update(float deltaTime);

        //initalize all systems (run init virtual function)
        void StartUp();

        //return the data linked with entity based on compType
        template<typename CompType>
        CompType* GetCompOfEntity(unsigned int entityID);

        //return managers
        ComponentManager &GetComponentManger() { return componentManager; }
        EntityManager &GetEntityManger() { return entityManager; }
        SystemManager &GetSystemManger() { return systemManager; }

    private:
        ComponentManager componentManager;
        EntityManager entityManager;
        SystemManager systemManager;
    };


    template<typename CompType>
    CompType* EcsEngine::GetCompOfEntity(unsigned int entityID){
        //gets ptr at component data
        auto* compData = componentManager.GetComponent<CompType>(entityManager.GetEntityRecord(entityID));
        //returns that bad boy
        return compData;
    }



}


#endif //BLOCKRPG_ECSENGINE_H
