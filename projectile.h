#include "vector2d.h"

class Projectile {
private:
    float g = 9.81;
    float time = 0;
    float timestep = 0.01;
    float height;
    int scale = 320;
    bool passFirstHalf = false;

public:
    Projectile(float h, float u, float tetra);
    ~Projectile();
    Vector2D init_pos;  //0,0 default
    Vector2D init_vel;
    Vector2D init_accel;
    Vector2D final_pos; //empty result
    Vector2D final_vel; //for calculate net velocity

    void setParameter(float h, float u, float tetra);
    int getPosX() {return (int)final_pos.getX();}
    int getPosY() {return (int)final_pos.getY();}
    float getInstantVelocity();
    float getInitVelocity();
    bool updatePos();
};
