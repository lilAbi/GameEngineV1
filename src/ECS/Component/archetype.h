
#ifndef BLOCKRPG_ARCHETYPE_H
#define BLOCKRPG_ARCHETYPE_H
#include <vector>
#include <unordered_map>
#include "component.h"
#include "componentArray.h"


namespace ECS{

    //collection of components that make up the foundations of an Entity
    class Archetype {
    public:
        using CompID = unsigned int;

        explicit Archetype() = default;
        ~Archetype() = default;

        //returns an index at the free position
        int GetNextFreePosition();

        //return ptr to ICompArray
        inline ECS::IComponentArray* GetCompArray(CompID compID) { return componentMap[compID];}

    public:
        //store which index is free in compDataArr
        unsigned int index{0};

        //maps a componentID to a block of memory containing the arary
        std::unordered_map<CompID, ECS::IComponentArray*> componentMap;

    };

}







#endif //BLOCKRPG_ARCHETYPE_H
