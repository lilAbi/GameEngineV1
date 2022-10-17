
#include "componentManager.h"

unsigned int ComponentManager::CreateArchetypeID(std::size_t numOfComps){
    //create ID for this archetype
    auto archeTypeID = util::TypeIDGenerator<ECS::Archetype>::GenNewID();

    //construct a new archetype obj and add to container
    archetypeDataContainer.try_emplace(archeTypeID, new ECS::Archetype);

    //return the newly created archetypeID
    return archeTypeID;
}

void ComponentManager::AddArchetypeToEntityRecord(ECS::EntityRecord& record, unsigned int archeID){
    //update entity's id and update the next free index
    record.archetypeID = archeID;
    record.index = archetypeDataContainer[archeID]->GetNextFreePosition();
}