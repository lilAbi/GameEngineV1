
#ifndef BLOCKRPG_MESHBUILDERSYSTEM_H
#define BLOCKRPG_MESHBUILDERSYSTEM_H
#include <unordered_map>
#include "ECS/System/system.h"
#include "RenderEngine/Core/mesh.h"
#include "GameEngine/Component/componentList.h"
#include "ECS/API.h"

#include <random>
#include <iomanip>

enum Face{
    FRONT = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3,
    BOTTOM = 4,
    TOP = 5,
};

//iterate thru entites that need the mesh builder system
//for terrain type entites perform a terrain mesh builder on part of the chunk or the whole chunk and update the data
//another entity will track if world needs to be redrawn or not
class MeshBuilderSystem : public ECS::ISystem {
public:
    MeshBuilderSystem() = default;
    ~MeshBuilderSystem() override = default;

    void PreUpdate(float deltaTime) override;
    void Update(float deltaTime) override;
    void PostUpdate(float deltaTime) override;

    void Init() override {}

    void BuildChunkGreedyMesh(Chunk& chunk, Mesh* mesh, glm::vec3 position);
    void AddFace(glm::vec3 position, Mesh* mesh, int blockID, float faceLength, float faceHeight, Face dimension);

    glm::vec3 GetColorOfBlock(int blockID){
        switch(blockID){
            case 1:
                return glm::vec3{192/255,192/255,192/255};
            case 2:
                return glm::vec3{ 0,255/255,0};
            default:
                return glm::vec3{0,0,0};
        }
    }

public:
    ECS::EcsEngine* ecsEngine{ECS::Initialize()};
    std::unordered_map<unsigned int, std::shared_ptr<Mesh>> meshContainer;
    bool first = true;
};


#endif //BLOCKRPG_MESHBUILDERSYSTEM_H
