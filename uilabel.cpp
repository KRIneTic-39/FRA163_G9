#include "gameobject.h"
#include <string>
#include <iomanip>
#include <sstream>

UILabel::UILabel(const char *texturesheet,int x, int y, unsigned int stringsize, float upBroad, const char *text, int fontsize){
    font = TTF_OpenFont(texturesheet, fontsize);                        //load font
    objectTex = TextureManager::loadText(font, text, black);

    sourceRec.x = 0;                //default at corner
    sourceRec.y = 0;                //default at corner

    TextureManager::getPixels(objectTex, &sourceRec.w, &sourceRec.h);   //get resolution of file and pass to sourceRec

    desRec.h = sourceRec.h;         //set desRec height
    desRec.w = sourceRec.w;         //set desRec width

    xpos = x;                       //set initial pos of desRec
    ypos = y;                       //set initial pos of desRec

    sizelimit = stringsize;         //set string maximum size
    upperBroader = upBroad;         //set upper broader
}

void UILabel::redraw(const char *text){
    TextureManager::destroyTex(objectTex);                              //destroy previous texture

    objectTex = TextureManager::loadText(font, text, black);            //load new texture

    TextureManager::getPixels(objectTex, &sourceRec.w, &sourceRec.h);   //get resolution of texture and pass to sourceRec

    desRec.h = sourceRec.h;         //set desRec height
    desRec.w = sourceRec.w;         //set desRec width
}

void UILabel::update(){
    if (Game::renderText && isSelected){
        //Text is not empty
        if (in != ""){
            //Render new text
            if (getValue() <= upperBroader){
                char arr[in.length() + 1];    //create char array
                strcpy(arr, in.c_str());      //convert string to char array
                redraw(arr);                  //redraw new text
            }
            else {
                std::stringstream stream;
                stream << std::fixed << std::setprecision(1) << upperBroader;
                in = stream.str();
                char arr[in.length() + 1];    //create char array
                strcpy(arr, in.c_str());      //convert string to char array
                redraw(arr);                  //redraw new text
            }
        }
        //Text is empty
        else {
            //Render space texture
            redraw("0");
        }
    }
    desRec.x = xpos - (desRec.w/2);
    desRec.y = 719 - ypos - (desRec.h/2);
}

void UILabel::render(){
    TextureManager::renderTex(objectTex, sourceRec, desRec);
}

void UILabel::clean(){
    TextureManager::destroyTex(objectTex);
    TextureManager::destroyFont(font);
}

float UILabel::getValue(){
    if (in == ""){
        return 0;
    }
    else if (in == "."){
        return 0;
    }
    else {
        return std::stof(in);
    }
}

void UILabel::setValue(float val, size_t n){
    in = std::to_string(val);
    in.resize(n);
    char arr[in.length() + 1];    //create char array
    strcpy(arr, in.c_str());      //convert string to char array
    redraw(arr);                  //redraw new text
}
