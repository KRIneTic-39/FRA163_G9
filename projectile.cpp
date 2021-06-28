#include "projectile.h"
#include <math.h>
#define _USE_MATH_DEFINES

Projectile::Projectile(float h, float u, float tetra){
    height = h * scale;
    init_vel.setX(cos(tetra*M_PI/180)*u);
    init_vel.setY(sin(tetra*M_PI/180)*u);
    init_accel.setY(-g);
}
void Projectile::setParameter(float h, float u, float tetra){
    init_pos.setX(0);
    init_pos.setY(0);
    height = h * scale;
    init_vel.setX(cos(tetra*M_PI/180)*u);
    init_vel.setY(sin(tetra*M_PI/180)*u);
    init_accel.setY(-g);
    final_pos.setX(0);
    final_pos.setY(0);
    time = 0;
}
bool Projectile::updatePos(){
    //if target is lower
    if (height < 0){
        if (final_pos.getY() > height){
            final_pos = (init_vel*time + init_accel*time*time*0.5)*scale;
            time = time + timestep;

            return true;     //if still update
        } else {
            return false;    //if finish update
        }
    }
    //if target is upper or equal
    else {
        if (final_pos.getY() > height){
            passFirstHalf = true;
        }
        if (final_pos.getY() <= height && passFirstHalf){
            passFirstHalf = false;
            return false;    //if finish update
        }
        else {
            final_pos = (init_vel*time + init_accel*time*time*0.5)*scale;
            time = time + timestep;
            return true;     //if still update
        }
    }
}

float Projectile::getInstantVelocity(){
    final_vel.setX(init_vel.getX());
    final_vel.setY(sqrt(pow(init_vel.getY(), 2) - 2*g*final_pos.getY()/scale));
    return final_vel.length();
}

float Projectile::getInitVelocity(){
    return sqrt(pow(init_vel.getX(), 2) + pow(init_vel.getY(), 2));
}
