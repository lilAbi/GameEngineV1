
#ifndef BLOCKRPG_ENTITYMANAGER_H
#define BLOCKRPG_ENTITYMANAGER_H

#include <unordered_map>
#include "ECS/Entity/entity.h"
#include "Utility/typeIDGenerator.h"

//create, read, update, and destroy entities
class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    using EntityID = unsigned int;

    //create entity
    unsigned int CreateEntity();

    //destroy entity - mark index free to overwrite
    void DestroyEntity(EntityID entityID);

    //gets the record of entity
    ECS::EntityRecord& GetEntityRecord(EntityID entityID){return entityRecordContainer[entityID];}

private:
    std::unordered_map<EntityID, ECS::EntityRecord> entityRecordContainer;
};


#endif //BLOCKRPG_ENTITYMANAGER_H
