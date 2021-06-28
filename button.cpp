#include "gameobject.h"

void Button::checkHovered(){
    SDL_Rect mouse_tip = {Game::inputManager.getMousePosX(),Game::inputManager.getMousePosY(), 1, 1};
    if (SDL_HasIntersection(&mouse_tip,&desRec)){
        isHovered = true;
        //changed texture and play thing
        sourceRec.x = sourceRec.w;
    } else {
        isHovered = false;
        sourceRec.x = 0;
        sourceRec.y = 0;
    }
}

void Button::update(){
    //object transition

    checkHovered();
    desRec.x = final_xpos - (desRec.w/2);
    desRec.y = 719 - final_ypos - (desRec.h/2);
}
