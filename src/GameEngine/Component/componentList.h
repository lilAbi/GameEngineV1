
#ifndef BLOCKRPG_COMPONENTLIST_H
#define BLOCKRPG_COMPONENTLIST_H

#include <memory>
#include "glm/glm.hpp"
#include "RenderEngine/Core/mesh.h"

//Holds a pointer to the mesh object of entity
struct MeshInstance{
    std::shared_ptr<Mesh> mesh;
};


//gives position of entity
struct Position{
    glm::vec3 position;
};


//within a chunk contains n x m x n block ids
struct Chunk{
    int blockID[16*16*16];
};
//contains all blocks in the world divided up into chunks
//chunks are arranged in a grid layout n x n
struct World{
    Chunk worldData[9*9*9];
};





#endif //BLOCKRPG_COMPONENTLIST_H
