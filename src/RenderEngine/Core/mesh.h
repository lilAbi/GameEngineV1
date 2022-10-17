
#ifndef BLOCKRPG_MESH_H
#define BLOCKRPG_MESH_H
#include <vector>
#include "glad/glad.h"
#include "glm/glm.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

class Mesh {
public:
    Mesh() { vertexData.reserve(26244); }
    ~Mesh() = default;

    void SetupMesh();
public:
    unsigned int VAO, VBO;
    std::vector<Vertex> vertexData;
};


#endif //BLOCKRPG_MESH_H
