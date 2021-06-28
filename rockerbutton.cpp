#include "gameobject.h"

void RockerButton::checkHovered(){
    SDL_Rect mouse_tip = {Game::inputManager.getMousePosX(),Game::inputManager.getMousePosY(), 1, 1};
    if (SDL_HasIntersection(&mouse_tip,&desRec)){
        isHovered = true;
    } else {
        isHovered = false;
    }
}

void RockerButton::checkSelected(){
    if (isSelected){
        sourceRec.x = sourceRec.w;
    }
    else if (!isSelected && isHovered){
        sourceRec.x = sourceRec.w;
    }
    else if(!isSelected && !isHovered){
        sourceRec.x = 0;
        sourceRec.y = 0;
    }
    else if(!isSelected){
        sourceRec.x = 0;
        sourceRec.y = 0;
    }
}

void RockerButton::update(){
    //object transition

    checkHovered();
    checkSelected();
    desRec.x = final_xpos - (desRec.w/2);
    desRec.y = 719 - final_ypos - (desRec.h/2);
}


