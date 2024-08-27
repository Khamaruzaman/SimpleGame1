#include <iostream>
#include "Game.h"


int main()
{
    // Init random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Init Game engine
    Game game;

    //Game Loop
    while(game.running())
    {

        //Update
        game.update();

        //Rendering
        game.render();



    }

    return 0;
}