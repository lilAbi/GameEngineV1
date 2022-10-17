
#include "entityManager.h"

//TODO:recycle entities recently sued
unsigned int EntityManager::CreateEntity() {
    //create entityID
    unsigned int newEntityID = util::TypeIDGenerator<EntityManager>::GenNewID();

    //insert into container with a null record (-1 index, 0 archetypeID)
    entityRecordContainer.emplace(newEntityID, ECS::EntityRecord{0, -1});

    return newEntityID;
}

void EntityManager::DestroyEntity(unsigned int entityID) {
    //"remove" entity
    //set record to 0
    //add entityid to rcycle list

}
