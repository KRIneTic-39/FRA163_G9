#include "inputmanager.h"
#include "iostream"

InputManager::InputManager(){}

void InputManager::pressKey(unsigned int keyID){
    keyMap[keyID] = true;   //assign keyID to map and set true
}
void InputManager::releaseKey(unsigned int keyID){
    keyMap[keyID] = false;  //assign keyID to map and set false
}
bool InputManager::isKeyPressed(unsigned int keyID){
    auto it = keyMap.find(keyID);
    if (it != keyMap.end()){
        // Found key in map
        return it->second;
    }
    else {
        // Didn't find key in map
        return false;
    }
}
void InputManager::setMousePos(float x, float y){
    mousePos.setX(x);
    mousePos.setY(y);
}
void InputManager::printMousePos(){
    std::cout << "Mouse position : " << mousePos.getX() << "," << 719 - mousePos.getY() << std::endl;
}
