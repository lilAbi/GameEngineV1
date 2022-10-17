#include "GameEngine/gameEngine.h"

int main() {
    //game application
    GameEngine game;
    //initialize game engine
    game.Init();
    //set up required systems
    game.Setup();
    //run game application
    game.Run();
    return 0;
}
