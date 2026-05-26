#include "engine/game.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        FPS::Game game(1920, 1080, "FPS Game - Core Engine");
        game.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
