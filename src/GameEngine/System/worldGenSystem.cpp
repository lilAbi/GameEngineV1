
#include "worldGenSystem.h"

void WorldGenSystem::PreUpdate(float deltaTime) {

}

void WorldGenSystem::Update(float deltaTime) {
    //is this first time world generation
    util::Logger::Log("WORLD GENERATION UPDATE");

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0, 2);

    //inital generation
    if(initalGen){

        //get associated data entity for a type 
        auto* data = ecsEngine->GetCompOfEntity<World>(2);

        for(auto& chunk : data->worldData){
            for(int& i : chunk.blockID){
                //i = (int)distr(eng);
                i = 1;
            }
        }

        initalGen = false;
    }

}

void WorldGenSystem::PostUpdate(float deltaTime) {


}
