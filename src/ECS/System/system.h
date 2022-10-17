
#ifndef BLOCKRPG_SYSTEM_H
#define BLOCKRPG_SYSTEM_H

#include "ECS/Component/component.h"
#include "Utility/typeIDGenerator.h"


namespace ECS{

    class ISystem{
    public:
        ISystem() = default;
        virtual ~ISystem() = default;

        using SystemID = unsigned int;

        virtual void PreUpdate(float deltaTime) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void PostUpdate(float deltaTime) = 0;

        virtual void Init() = 0;

    public:
        SystemID systemID = util::TypeIDGenerator<ISystem>::GenNewID();
        bool needUpdate = true;
        bool needPreUpdate = true;
        bool needPostUpdate = true;
        bool systemEnabled = true;
    };


}



#endif //BLOCKRPG_SYSTEM_H
