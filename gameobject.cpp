#include "gameobject.h"

GameObject::GameObject(const char *texturesheet,int x, int y, int scale, enum Type type)
{
    objectTex = TextureManager::loadTexture(texturesheet);              //load object texture from file name

    sourceRec.x = 0;                    //default at corner
    sourceRec.y = 0;                    //default at corner
    TextureManager::getPixels(objectTex, &sourceRec.w, &sourceRec.h);   //get resolution of file and pass to sourceRec

    desRec.h = sourceRec.h / scale;     //set desRec height

    if (type == DOUBLE){
        sourceRec.w /= 2;
        desRec.w = sourceRec.w / scale; //set desRec width
    }
    else if (type == NORMAL){
        desRec.w = sourceRec.w / scale; //set desRec width
    }

    init_xpos = final_xpos = x;         //set initial pos of desRec
    init_ypos = final_ypos = y;         //set initial pos of desRec
}

GameObject::~GameObject(){
    clean();
}

void GameObject::update(){
    //object transition
    desRec.x = final_xpos - (desRec.w/2);
    desRec.y = 719 - final_ypos - (desRec.h/2);
}

void GameObject::render(){
    TextureManager::renderTex(objectTex, sourceRec, desRec);
}

void GameObject::clean(){
    TextureManager::destroyTex(objectTex);
}
