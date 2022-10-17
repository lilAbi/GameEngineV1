
#ifndef BLOCKRPG_SYSTEMMANAGER_H
#define BLOCKRPG_SYSTEMMANAGER_H
#include <map>
#include <vector>
#include <memory>

#include "ECS/System/system.h"
#include "Utility/logger.h"

//add and remove systems
//run update
class SystemManager {
public:

    //add system to container of systems to run
    template<typename S, typename ...Args>
    void AddSystem(Args&& ...args);

    //update function to run systems
    void Update(float deltaTime);

    void StartUpSystems();

private:
    //contains all the systems that are registered to the engine
    std::map< unsigned int, std::shared_ptr<ECS::ISystem> > systemContainer;
    //defines the order in which system will execute first:
    std::vector< std::shared_ptr<ECS::ISystem> > systemExecuteOrder;
};

template<typename S, typename ...Args>
void SystemManager::AddSystem(Args&& ...args){
    //create a system with a system ID
    std::shared_ptr<ECS::ISystem> newSystem = std::make_shared<S>(std::forward<Args>(args)...);

    //add it to the systemContainer
    systemContainer.emplace(newSystem->systemID, newSystem);

    //add id to the systemExecuteOrder
    systemExecuteOrder.push_back(newSystem);
}


#endif //BLOCKRPG_SYSTEMMANAGER_H
