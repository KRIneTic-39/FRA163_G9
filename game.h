#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "inputmanager.h"

class Game {
private:
    bool isRunning;
    int u_count = 0;
    SDL_Event event;
public:
    Game();
    ~Game();
    void init(const char *title,int x, int y, int w, int h);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool checkRunning() {return isRunning;}
    static SDL_Window *window;
    static SDL_Renderer *renderer;      //for create one and only renderer for entire project
    static InputManager inputManager;   //for create one and only input for entire project
    static bool renderText;             //for telling UI label when to render new text
};
