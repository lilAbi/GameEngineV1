#include "gameEngine.h"

void GameEngine::Init() {
    //initialize window
    window.Init();

    //activate ECS engine
    ecsEngine = ECS::Initialize();
}

void GameEngine::Setup() {
    ComponentManager& compManager = ecsEngine->GetComponentManger();
    EntityManager& entityManager = ecsEngine->GetEntityManger();
    SystemManager& sysManager = ecsEngine->GetSystemManger();

    //create Archetype IDS
    auto playerArcheID = compManager.CreateArchetypeID(1);
    auto worldArcheID = compManager.CreateArchetypeID(3);

    //TODO: only default initialization
    //register archetypes
    compManager.RegisterArchetype(playerArcheID, 1,ECS::Component<Position>());
    compManager.RegisterArchetype(worldArcheID, 1,  ECS::Component<World>(), ECS::Component<MeshInstance>(), ECS::Component<Position>());

    //creating entity tags
    auto entityPlayerID = entityManager.CreateEntity();
    auto entityWorldID = entityManager.CreateEntity();
    compManager.AddArchetypeToEntityRecord(entityManager.GetEntityRecord(entityPlayerID), playerArcheID);
    compManager.AddArchetypeToEntityRecord(entityManager.GetEntityRecord(entityWorldID), worldArcheID);

    //create a system
    sysManager.AddSystem<WorldGenSystem>();
    sysManager.AddSystem<MeshBuilderSystem>();
    sysManager.AddSystem<RenderSystem>(window());

    //run init system functions basically 
    ecsEngine->StartUp();
}


void GameEngine::Run() {

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while(!glfwWindowShouldClose(window() )){
        util::Logger::Log("NEW FRAME");
        //calculate delta time (time between current and last frame)
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //update the ECS Engine
        ecsEngine->Update(deltaTime);

        //poll events
        glfwPollEvents();

        //break;
    }

    //destory ecs engine
    ECS::Destroy();
}
