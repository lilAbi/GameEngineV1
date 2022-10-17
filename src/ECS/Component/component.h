
#ifndef BLOCKRPG_COMPONENT_H
#define BLOCKRPG_COMPONENT_H

#include <array>
#include "Utility/typeIDGenerator.h"
#include "Utility/logger.h"

namespace ECS {

    //base component class
    class IComponent{
    public:
        IComponent() = default;
        virtual ~IComponent()= default;

        virtual unsigned int GetSizeOfComp() = 0;
        virtual unsigned int GetCompID() = 0;

    };

    //all types of components will be inherited from this class
    template<typename ComponentType>
    class Component : public IComponent {
    public:
        using CompType = ComponentType;

        Component() {
            (componentID == 0) && (componentID = util::TypeIDGenerator<IComponent>::GenNewID());
            util::Logger::Log("Constructing Component ID: " + std::to_string(componentID));
        }

        Component(const Component&& otherComponent) noexcept {
            componentID = otherComponent.componentID;
            util::Logger::Log("Moving Component ID: " + std::to_string(componentID));
        }

        ~Component() override = default;

        unsigned int GetSizeOfComp() override { return sizeof(ComponentType); }
        unsigned int GetCompID() override { return componentID; }

    private:
        inline static unsigned int componentID = 0;
    };

}

#endif //BLOCKRPG_COMPONENT_H
