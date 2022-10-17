
#ifndef BLOCKRPG_WORLDGENSYSTEM_H
#define BLOCKRPG_WORLDGENSYSTEM_H
#include "ECS/System/system.h"
#include "ECS/API.h"
#include "GameEngine/Component/componentList.h"
#include "glm/glm.hpp"

#include <random>
#include <iomanip>



class WorldGenSystem : public ECS::ISystem  {
public:
    WorldGenSystem() = default;
    ~WorldGenSystem() override = default;

    void PreUpdate(float deltaTime) override;
    void Update(float deltaTime) override;
    void PostUpdate(float deltaTime) override;

    void Init() override {}
private:

    ECS::EcsEngine* ecsEngine{ECS::Initialize()};
    bool initalGen = true;

};


#endif //BLOCKRPG_WORLDGENSYSTEM_H
