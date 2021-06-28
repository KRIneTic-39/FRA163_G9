#include "gameobject.h"

Projectile SquashBall::*trajectory; //initialized trajectory for squash ball

void SquashBall::reset(){
    final_xpos = init_xpos;         //reset final pos to initial pos
    final_ypos = init_ypos;         //reset final pos to initial pos

    //delete all object in vector point
    for (unsigned int j = 0; j < point.size(); j++){
        delete point[j];
    }
    //empty vector point
    point.clear();
    //reset state finish
    isProjectileFinish = false;
}

void SquashBall::setProjectile(float height, float netVel, float angle){
    //Do first time only
    if (init == true){
        trajectory = new Projectile(height, netVel, angle); //***
        init = false;
    }
    //Do second time and so on
    else {
        trajectory->setParameter(height, netVel, angle);    //***
    }
    isProjectile = true;
    startProjectile = false;

    //get initial net velocity and initial position
    net_vel = trajectory->getInitVelocity();
    real_x = trajectory->init_pos.getX();
    real_y = trajectory->init_pos.getY() + 0.537;
}

void SquashBall::update(){
    //object transition
    if (isProjectile && startProjectile){

        if (trajectory->updatePos()){                 //update projectile and get state
            final_xpos = init_xpos + trajectory->getPosX(); //instant position
            final_ypos = init_ypos + trajectory->getPosY(); //instant position

            point.push_back(new Object("assets/traject.png", final_xpos, final_ypos, 2, NORMAL));   //append new object
            point[point.size()-1]->update();

            net_vel = trajectory->getInstantVelocity();             //update net velocity
            real_x = (trajectory->final_pos.getX()/320);            //update real x
            real_y = (trajectory->final_pos.getY()/320) + 0.537;    //update real y
        }
        else {
            //finished projectile
            startProjectile = false;
            isProjectileFinish = true;
        }
    }

    desRec.x = final_xpos - (desRec.w/2);
    desRec.y = 719 - final_ypos - (desRec.h/2);
}

void SquashBall::render(){
    //render trajectory from vector point
    if (point.size() != 0){
        for (unsigned int j = 0; j < point.size(); j++){
            point[j]->render();
        }
    }
    //render basketball
    TextureManager::renderTex(objectTex, sourceRec, desRec);
}

void SquashBall::clean(){
    TextureManager::destroyTex(objectTex);
}

