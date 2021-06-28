#include "vector2d.h"
#include <unordered_map>

class InputManager{
private:
    std::unordered_map<unsigned int, bool> keyMap;
    Vector2D mousePos;
public:
    InputManager();
    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);
    bool isKeyPressed(unsigned int keyID);
    void setMousePos(float x, float y);

    void printMousePos();
    int getMousePosX() {return (int)mousePos.getX();}
    int getMousePosY() {return (int)mousePos.getY();}
};
