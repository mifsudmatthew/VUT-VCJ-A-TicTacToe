#include <iostream>
#include "Game.h"

int main()
{
    Game* game = new Game(); // Creating a new game object

    // Executing the game by using the run() method.
    if (game->run() == 0) {
        return EXIT_SUCCESS;
    }else{
        return EXIT_FAILURE;
    }
}