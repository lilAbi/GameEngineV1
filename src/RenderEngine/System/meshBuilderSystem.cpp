
#include "RenderEngine/System/meshBuilderSystem.h"

void MeshBuilderSystem::PreUpdate(float deltaTime) {

    //check if mesh needs rebuilding for particular
    //does mesh need to be fully built

    if(first) {
        //get associated data entity for a type
        auto *meshInstanceData = ecsEngine->GetCompOfEntity<MeshInstance>(2);
        //possible error, since meshdata return might also be nullptr if mesh component doesn't actually exist
        if (meshInstanceData != nullptr) {
            auto meshPtr = std::make_shared<Mesh>();
            meshContainer.emplace(2, meshPtr);
            meshInstanceData->mesh = meshPtr;
        }
    }
}

void MeshBuilderSystem::Update(float deltaTime) {

    if(first){
        auto* meshInstanceData = ecsEngine->GetCompOfEntity<MeshInstance>(2);
        auto* worldData = ecsEngine->GetCompOfEntity<World>(2);
        auto* posData = ecsEngine->GetCompOfEntity<Position>(2);

        int zFactor{0};
        int yFactor{0};

        for(int i = 0; i < (9*9*9); i++){
            if( (i%9 == 0) && i !=0) {
                zFactor++;
            }
            if( (i % (9*9) == 0) && i != 0 ){
                yFactor++;
                zFactor = 0;
            }
            glm::vec3 chunkPosition{posData->position.x + (static_cast<float>(i%9)*16), posData->position.y + (yFactor*16), posData->position.z + (zFactor*16) };

            //build chunk and push into mesh
            BuildChunkGreedyMesh(worldData->worldData[i], meshInstanceData->mesh.get(), chunkPosition);
        }

        meshInstanceData->mesh->SetupMesh();
        //first = false;
    }

}

void MeshBuilderSystem::PostUpdate(float deltaTime) {}

void MeshBuilderSystem::BuildChunkGreedyMesh(Chunk& chunk, Mesh* mesh, glm::vec3 position){

    //lamada function to get blockID from chunk given x,y,z coords
    auto GetBlockID = [&chunk](int x, int y, int z) -> int {
        if(x > 16 || y > 16 || z > 16) { return 0; }
        return chunk.blockID[ x + (16*z) + (16*16*y) ];
    };

    //iterate a 2d slice of the chunk through 6 different faces
    int dimension  = 0;
    for(int dimension  = 0; dimension < 6; dimension++){
        //when filled counter is equal to 16*16 then that chunk doesnt need to add anymore faces on that dimension
        int filledCounter = 0;
        //2d grid to represent if there is a block in front of the next slice of the current slice
        bool filled[16*16]{false};

        for(int i = 0; i < 16; i++){
            //create a mask of current slice
            int mask[16*16]{0};

            //fill mask with blockIDs of current silce
            for(int j = 0; j < 16; j++){
                for(int k = 0; k < 16; k++) {
                    //if block is infront of another block
                    if(filled[k + (16 * j)]) continue;

                    //fill mask at current position based on the dimension currently being iterated
                    //switch to switch statement and then have the height correlate with the
                    int currentBlockID = 0;
                    switch(Face(dimension)){
                        case FRONT:
                            currentBlockID = GetBlockID(k, j, i);
                            break;
                        case BACK:
                            currentBlockID = GetBlockID(k, j, (15-i));
                            break;
                        case LEFT:
                            currentBlockID = GetBlockID(i, j, k);
                            break;
                        case RIGHT:
                            currentBlockID = GetBlockID((15-i), j, k);
                            break;
                        case BOTTOM:
                            currentBlockID = GetBlockID(k, i, j);
                            break;
                        case TOP:
                            currentBlockID = GetBlockID(k, (15-i), j);
                            break;
                        default:
                            break;
                    }
                    mask[k + (16 * j)] = currentBlockID;

                    //if not filled and the block id is not an air
                    if( (!filled[k + (16 * j)]) && (currentBlockID != 0) ) {
                        filled[k + (16 * j)] = true;
                        filledCounter++;
                    }

                }
            }//end of filling mask loop

            //go thru the mask and mesh like blocks and add it to meshcontainer
            for(int y = 0; y < 16; y++){
                for(int x = 0; x < 16; x++){
                    //get current block ID
                    auto currentBlockID = mask[x + (16*y)];

                    //if the block is air then just skip
                    if(currentBlockID == 0) continue;

                    //look at next mask position and if the same as the current block
                    int maxLength = 1;
                    while((x+maxLength < 16)){
                        if( currentBlockID == mask[x+maxLength + (16*y)] ){
                            maxLength++;
                        } else {
                            break;
                        }
                    }//end of finding length

                    //finds the maximum height of the loop
                    int maxHeight = 1;
                    bool needBreak = false;
                    for(int h = y+maxHeight; h < 16; h++){
                        for(int l = 0; l < maxLength; l++){
                            if(currentBlockID != mask[l + (16*h)]) {
                                needBreak = true;
                                break;
                            }
                        }
                        if(needBreak) break;
                        maxHeight++;
                    }//end of finding height loop

                    //clear the mask sections that is going to be meshed
                    for(int a = y; a < y+maxHeight; a++){
                        for(int b = x; b < x+maxLength; b++){
                            mask[b+(16*a)] = 0;
                        }
                    }//end of clearing mask loop


                    glm::vec3 quadStart{position};
                    //correct the offset
                    switch(dimension){
                        case FRONT:
                            quadStart.x += x;
                            quadStart.y += y;
                            quadStart.z += i;
                            break;
                        case BACK:
                            quadStart.x += (x);
                            quadStart.y += (y);
                            quadStart.z += (15-i);
                            break;
                        case LEFT:
                            quadStart.x += i;
                            quadStart.y += y;
                            quadStart.z += x;
                            break;
                        case RIGHT:
                            quadStart.x += (15-i);
                            quadStart.y += (y);
                            quadStart.z += (x);
                            break;
                        case BOTTOM:
                            quadStart.x += x;
                            quadStart.y += i;
                            quadStart.z += y;
                            break;
                        case TOP:
                            quadStart.x += (x);
                            quadStart.y += (15-i);
                            quadStart.z += (y);
                            break;
                        default:
                            break;
                    }
                    //add face
                    AddFace(quadStart, std::forward<Mesh*>(mesh), currentBlockID, (float)maxLength, (float)maxHeight, Face(dimension));
                }
            }//end of meshing

            //mesh the next dimension of the chunk when no more meshing needs to be done for this side
            if(filledCounter == 16*16){break;}

        }//end of slice shifter
    }//end of dimension loop

}//end of function

/*  face
 *  V1 ----- V4
 *  |        |
 *  |        |
 *  V2------V3
 */

void MeshBuilderSystem::AddFace(glm::vec3 position, Mesh* mesh, int blockID, float faceLength, float faceHeight, Face dimension){

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0, 1);

    glm::vec3 color{distr(eng), distr(eng), distr(eng)};

    switch(dimension){
        case BACK:
            position.z += 1;
            break;
        case RIGHT:
            position.x += 1;
            break;
        case TOP:
            position.y += 1;
            break;
        default:
            break;
    }

    glm::vec3 v1{position}, v2{position}, v3{position}, v4{position};

    switch(dimension){
        case Face::FRONT:
        case Face::BACK:
            v1.y += faceHeight;
            v3.x += faceLength;
            v4.x += faceLength; v4.y += faceHeight;
            break;
        case Face::LEFT:
        case Face::RIGHT:
            v1.y += faceHeight; v1.z += faceLength;
            v2.z += faceLength;
            v4.y += faceHeight;
            break;
        case Face::TOP:
        case Face::BOTTOM:
            v1.z += faceHeight;
            v3.x += faceLength;
            v4.x += faceLength; v4.z += faceHeight;
            break;
        default:
            break;
    }

    //v4->v3->v2
    mesh->vertexData.push_back(Vertex{v4,color});
    mesh->vertexData.push_back(Vertex{v3,color});
    mesh->vertexData.push_back(Vertex{v2,color});
    //v2->v1->v4
    mesh->vertexData.push_back(Vertex{v2,color});
    mesh->vertexData.push_back(Vertex{v1,color});
    mesh->vertexData.push_back(Vertex{v4,color});

}