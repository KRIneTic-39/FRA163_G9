#include "game.h"

Game *g_game = nullptr;

int main(int argc, char **argv)
{
    const int fps = 60;                 //limiting frame rate
    const int frameDelay = 1000/fps;    //limiting frame rate
    Uint32 frameStart;                  //limiting frame rate
    int frameTime;                      //limiting frame rate

    g_game = new Game();

    g_game->init("FRA163 Group-9 Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720);   //1280x720

    while (g_game->checkRunning()){                 //Game loop
        frameStart = SDL_GetTicks();                //limiting frame rate

        g_game->handleEvents();                     //input handling
        g_game->update();                           //change object attribute
        g_game->render();                           //display

        frameTime = SDL_GetTicks() - frameStart;    //limiting frame rate
        if (frameDelay > frameTime){                //limiting frame rate
            SDL_Delay(frameDelay - frameTime);
        }
    }
    g_game->clean();

    return 0;
}
