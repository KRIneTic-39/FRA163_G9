#include "game.h"
#include "texturemanager.h"
#include "projectile.h"
#include <vector>

enum Type {NORMAL, DOUBLE};     //Global Game Object Type

//SDL Object
class GameObject{
protected:
    int init_xpos;              //initial position must be constant and saved
    int init_ypos;              //initial position must be constant and saved
    int final_xpos;             //final position change by time
    int final_ypos;             //final position change by time
    SDL_Texture *objectTex = nullptr;
    SDL_Rect sourceRec, desRec;
public:
    GameObject(const char *texturesheet,int x, int y, int scale, enum Type type);  //create GameObject with initial parameter
    virtual ~GameObject();      //https://www.geeksforgeeks.org/virtual-destructor/
    virtual void update();
    virtual void render();
    virtual void clean();
};

class Object : public GameObject{
public:
    Object(const char *texturesheet, int x, int y, int scale, enum Type type) : GameObject(texturesheet, x, y, scale, type) {}
    ~Object(){}
    void setPos(int x, int y){final_xpos = x;final_ypos = y;}
    void render() override {if (showTexture == true){TextureManager::renderTex(objectTex, sourceRec, desRec);}}
    bool showTexture = true;
};

class Map : public GameObject{
public:
    Map(const char *texturesheet, int x, int y, int scale, enum Type type) : GameObject(texturesheet, x, y, scale, type) {}
    ~Map(){}
    void update() override;
};

class SquashBall : public GameObject{
private:
    Projectile *trajectory;       //initialized trajectory for squash ball
    std::vector<Object*> point;
    bool init = true;             //use in setProjectile
public:
    SquashBall(const char *texturesheet, int x, int y, int scale, enum Type type) : GameObject(texturesheet, x, y, scale, type) {}
    ~SquashBall(){}
    void reset();                 //reset to initial position and empty vector point
    void setProjectile(float height, float netVel, float angle);
    void update() override;
    void render() override;
    void clean() override;
    bool isProjectile = false;
    bool startProjectile;
    bool isProjectileFinish = false;
    float net_vel, real_x, real_y;
};

class Button : public GameObject{
private:
    void checkHovered();
public:
    Button(const char *texturesheet, int x, int y, int scale, enum Type type) : GameObject(texturesheet, x, y, scale, type) {}
    ~Button(){}
    void update() override;
    bool isHovered;             //for stored hover status
};

class RockerButton : public GameObject{
private:
    void checkHovered();
    void checkSelected();
public:
    RockerButton(const char *texturesheet, int x, int y, int scale, enum Type type) : GameObject(texturesheet, x, y, scale, type) {}
    ~RockerButton(){}
    void update() override;
    bool isHovered;             //for stored hover status
    bool isSelected = false;    //for stored button status
};

//TTF Object
class UILabel {
private:
    int xpos;
    int ypos;
    SDL_Texture *objectTex = nullptr;
    SDL_Rect sourceRec, desRec;
    TTF_Font *font = nullptr;
    SDL_Color black = {0, 0, 0, 0};
    float upperBroader;
public:
    //create UI label with initial position,font style and size
    UILabel(const char *texturesheet,int x, int y, unsigned int stringsize, float upBroad, const char *text, int fontsize);
    ~UILabel();
    void redraw(const char *text);
    void update();
    void render();
    void clean();
    bool isSelected = false;            //for stored button status
    std::string in = "";                //string for store
    unsigned int sizelimit;             //string maximum size
    float getValue();                   //string to float
    void setValue(float val, size_t n); //bypass text input
};
