
#ifndef BLOCKRPG_COMPONENTMANAGER_H
#define BLOCKRPG_COMPONENTMANAGER_H

#include <vector>
#include <memory>
#include <unordered_map>

#include "ECS/Component/component.h"
#include "ECS/Component/archetype.h"
#include "ECS/Entity/entity.h"
#include "Utility/logger.h"
#include "Utility/typeIDGenerator.h"


//Manages components
class ComponentManager {
public:
    ComponentManager() = default;
    ~ComponentManager() = default;

    using ArchetypeID = unsigned int;

    //create an archetype index
    unsigned int CreateArchetypeID(std::size_t numOfComps);
    //Registers a group of components to make an Archetype
    template<typename CompType, typename ...CompTypes>
    void RegisterArchetype(ArchetypeID archeTypeID, int compDataSize, CompType&& arg, CompTypes&& ...args);
    //takes in an entity record and updates the archetype ptr and gets next free index
    void AddArchetypeToEntityRecord(ECS::EntityRecord& record, unsigned int archeID);
    //returns archetype data
    inline ECS::Archetype* GetArchetype(ArchetypeID archetypeID) {return archetypeDataContainer[archetypeID];}

    template<typename CompType>
    CompType* GetComponent(ECS::EntityRecord& record);

private:
    //base case for when RegisterArchetype when arguments run out until archetypeIndex
    static void RegisterArchetype(ArchetypeID archeTypeID, int compDataSize){}

private:
    //store a list of components active
    std::unordered_map<ArchetypeID, ECS::Archetype*> archetypeDataContainer;
};


//order of construction is right to left
template<typename CompType, typename ...CompTypes>
void ComponentManager::RegisterArchetype(ArchetypeID archeTypeID, const int compDataSize, CompType&& arg, CompTypes&& ...args) {
    util::Logger::Log("Registering Archetype");

    //point to the archetypedata object for this archetype
    ECS::Archetype* archeTypeData = GetArchetype(archeTypeID);

    //bind temporary to non const lvalue reference to extend duration
    CompType& test = arg;

    archeTypeData->componentMap.emplace(arg.GetCompID(), new ECS::ComponentArray<typename CompType::CompType>(compDataSize));

    //go through the next argument in the parameter pack until base class
    RegisterArchetype(  std::forward<unsigned int>(archeTypeID),
                        std::forward<unsigned int>(compDataSize),
                        std::forward<CompTypes>(args)...);

}//back to front of args


template<typename CompType>
CompType* ComponentManager::GetComponent(ECS::EntityRecord& record){
    using CompArr = ECS::ComponentArray<CompType>;
    ECS::Component<CompType> comp;

    //get archetype data
    ECS::Archetype* archeTypeData = GetArchetype(record.archetypeID);

    //downcast to get array with associated type
    auto* dataArray = reinterpret_cast<CompArr*>(archeTypeData->GetCompArray(comp.GetCompID()));

    //return the object associated at the index
    return (dataArray) ? dataArray->GetDataAt(record.index) : nullptr;
}



#endif //BLOCKRPG_COMPONENTMANAGER_H
