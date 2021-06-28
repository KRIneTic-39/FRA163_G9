#include "gameobject.h"
#include <fstream>
#include <math.h>
#define _USE_MATH_DEFINES
using namespace std;

//Static Game Object
Object *red;
Object *green;
Object *k_yellow;
Object *x_yellow;
Object *m_error;
Object *xpos_error;
Object *k_error;
Object *x_error;
Object *hoop;
SquashBall *squash;
Map *background;
Button *save;
Button *reset;
Button *start;
Button *calculate;
Button *clear;
UILabel *text[8];
UILabel *vel_gauge;
UILabel *x_gauge;
UILabel *y_gauge;
RockerButton *textbox[8];

float last_height;
float last_vel;
float last_angle;

bool k_isSelected = false;
bool x_isSelected = false;

//For Save Process
bool allowSave = false;
string las_mass;
string las_x;
string las_y;
string las_k;
string las_spx;
string las_vel;

float find_x1(float a,float b,float c){
    float x1,d;
    d = b*b - 4*a*c;

    if (d > 0) {
        x1 = (-b + sqrt(d)) / (2*a);
    }
    else if (d == 0) {
        x1 = -b/(2*a);
    }
    return x1;
}

class ObjectManager{
public:
    static void initObject();
    static void buttonHandle();
    static void updateAllObject();
    static void renderAllObject();
    static void cleanAllObject();
    static void recallObject();
    static void clearPanal();
    static void textboxesDeselectExcept(int i);
    static void calculateProjectile();
    static void saveToFile();
};

void ObjectManager::initObject(){
    //Static Game Object
    red = new Object("assets/red.png", 772, 105, 1, NORMAL);
    green = new Object("assets/green.png", 882, 105, 1, NORMAL);
    k_yellow = new Object("assets/blockyellow.png", 241, 223, 1, NORMAL);
    x_yellow = new Object("assets/blockyellow.png", 264, 169, 1, NORMAL);
    m_error = new Object("assets/blockred1.png", 164, 495, 1, NORMAL);
    xpos_error = new Object("assets/blockred1.png", 163, 390, 1, NORMAL);
    k_error = new Object("assets/blockred2.png", 241, 223, 1, NORMAL);
    x_error = new Object("assets/blockred2.png", 264, 169, 1, NORMAL);
    hoop = new Object("assets/hoop.png", 572, 326, 1, NORMAL);
    red->showTexture = false;
    green->showTexture = true;
    k_yellow->showTexture = false;
    x_yellow->showTexture = false;
    m_error->showTexture = false;
    xpos_error->showTexture = false;
    k_error->showTexture = false;
    x_error->showTexture = false;
    hoop->showTexture = false;

    //Squashball
    squash = new SquashBall("assets/Basketball.png", 572, 388, 1, NORMAL);

    //Button
    save = new Button("assets/save.png", 1175, 657, 1, DOUBLE);
    reset = new Button("assets/reset.png", 1176, 105, 1, DOUBLE);
    start = new Button("assets/start.png", 1017, 105, 1, DOUBLE);
    calculate = new Button("assets/calculate.png", 168, 44, 1, DOUBLE);
    clear = new Button("assets/clear.png", 327, 44, 1, DOUBLE);

    //Map
    background = new Map("assets/screen2.png", 0, 0, 1, NORMAL);

    //UI Label - "9999999.99", "999.99"
    //in = "" will show 0 on screen
    text[0] = new UILabel("assets/arial.ttf", 166, 595, 10, 1000, "0", 20);
    text[1] = new UILabel("assets/arial.ttf", 165, 544, 10, 1000, "0.537", 20);
    text[2] = new UILabel("assets/arial.ttf", 164, 495, 10, 600, "0", 20);
    text[3] = new UILabel("assets/arial.ttf", 163, 390, 10, 2.1, "0", 20);
    text[4] = new UILabel("assets/arial.ttf", 162, 337, 10, 0.6, "0", 20);
    text[5] = new UILabel("assets/arial.ttf", 264, 282, 6, 90, "45", 20);
    text[6] = new UILabel("assets/arial.ttf", 241, 223, 6, 2000, "0", 20);
    text[7] = new UILabel("assets/arial.ttf", 264, 169, 6, 32, "0", 20);
    vel_gauge = new UILabel("assets/arial.ttf", 588, 144, 6, 1000, "0", 20);
    x_gauge = new UILabel("assets/arial.ttf", 588, 108, 6, 1000, "0", 20);
    y_gauge = new UILabel("assets/arial.ttf", 588, 72, 6, 1000, "0", 20);

    //Text Hit Box
    textbox[0] = new RockerButton("assets/block3.png", 166, 595, 1, DOUBLE);
    textbox[1] = new RockerButton("assets/block3.png", 165, 544, 1, DOUBLE);
    textbox[2] = new RockerButton("assets/block.png", 164, 495, 1, DOUBLE);
    textbox[3] = new RockerButton("assets/block.png", 163, 390, 1, DOUBLE);
    textbox[4] = new RockerButton("assets/block.png", 162, 337, 1, DOUBLE);
    textbox[5] = new RockerButton("assets/block4.png", 263, 282, 1, DOUBLE);
    textbox[6] = new RockerButton("assets/block2.png", 241, 223, 1, DOUBLE);
    textbox[7] = new RockerButton("assets/block2.png", 264, 169, 1, DOUBLE);
}

void ObjectManager::buttonHandle(){
    if (save->isHovered){
        SDL_StopTextInput();
        textboxesDeselectExcept(-1);
        //cout << "Save is pressed" << endl;
        if (squash->isProjectile && allowSave){
            saveToFile();
        }
        else {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Information", "Please enter parameter and press Calculate", Game::window);
        }
    }
    else if (reset->isHovered){
        SDL_StopTextInput();
        textboxesDeselectExcept(-1);
        //cout << "Reset is pressed" << endl;
        if (squash->isProjectile && squash->isProjectileFinish){
            recallObject();
        }
        else if (!squash->isProjectile) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Information", "Please enter parameter and press Calculate", Game::window);
        }
    }
    else if (start->isHovered){
        SDL_StopTextInput();
        textboxesDeselectExcept(-1);
        //cout << "Start is pressed" << endl;
        if (squash->isProjectile && !squash->isProjectileFinish){
            squash->startProjectile = true;
        }
        else if (!squash->isProjectile && !squash->isProjectileFinish){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Information", "Please enter parameter and press Calculate", Game::window);
        }
    }
    else if (calculate->isHovered){
        SDL_StopTextInput();
        textboxesDeselectExcept(-1);
        //cout << "Calculate is pressed" << endl;
        calculateProjectile();
    }
    else if (clear->isHovered){
        SDL_StopTextInput();
        textboxesDeselectExcept(-1);
        //cout << "Clear is pressed" << endl;
        clearPanal();
    }
    else if (textbox[0]->isHovered){
        SDL_StartTextInput();
        textbox[0]->isSelected = text[0]->isSelected = false;
        textboxesDeselectExcept(0);
        //cout << "textbox[0] is pressed" << endl;
    }
    else if (textbox[1]->isHovered){
        SDL_StartTextInput();
        textbox[1]->isSelected = text[1]->isSelected = false;
        textboxesDeselectExcept(1);
        //cout << "textbox[1] is pressed" << endl;
    }
    else if (textbox[2]->isHovered){
        SDL_StartTextInput();
        textbox[2]->isSelected = text[2]->isSelected = true;
        textboxesDeselectExcept(2);
        //cout << "textbox[2] is pressed" << endl;
    }
    else if (textbox[3]->isHovered){
        SDL_StartTextInput();
        textbox[3]->isSelected = text[3]->isSelected = true;
        textboxesDeselectExcept(3);
        //cout << "textbox[3] is pressed" << endl;
    }
    else if (textbox[4]->isHovered){
        SDL_StartTextInput();
        textbox[4]->isSelected = text[4]->isSelected = true;
        textboxesDeselectExcept(4);
        //cout << "textbox[4] is pressed" << endl;
    }
    else if (textbox[5]->isHovered){
        SDL_StartTextInput();
        textbox[5]->isSelected = text[5]->isSelected = false;
        textboxesDeselectExcept(5);
        //cout << "textbox[5] is pressed" << endl;
    }
    else if (textbox[6]->isHovered){
        SDL_StartTextInput();
        textbox[6]->isSelected = text[6]->isSelected = true;
        textboxesDeselectExcept(6);
        //cout << "textbox[6] is pressed" << endl;
        k_isSelected = x_yellow->showTexture = true;
        x_isSelected = k_yellow->showTexture = false;
        text[6]->in.clear();
        text[6]->redraw("0");
        text[7]->in.clear();
        text[7]->redraw("Output");
    }
    else if (textbox[7]->isHovered){
        SDL_StartTextInput();
        textbox[7]->isSelected = text[7]->isSelected= true;
        textboxesDeselectExcept(7);
        //cout << "textbox[7] is pressed" << endl;
        k_isSelected = x_yellow->showTexture = false;
        x_isSelected = k_yellow->showTexture = true;
        text[7]->in.clear();
        text[7]->redraw("0");
        text[6]->in.clear();
        text[6]->redraw("Output");
    }
    else {  //make other deselected
        SDL_StopTextInput();
        textboxesDeselectExcept(-1);
        //cout << "all button are not pressed" << endl;
    }
}

void ObjectManager::updateAllObject(){
    if (squash->startProjectile && !squash->isProjectileFinish){
        red->showTexture = true;
        green->showTexture = false;
    } else {
        red->showTexture = false;
        green->showTexture = true;
    }
    background->update();
    red->update();
    green->update();
    k_yellow->update();
    x_yellow->update();
    m_error->update();
    xpos_error->update();
    k_error->update();
    x_error->update();
    squash->update();
    hoop->update();
    save->update();
    reset->update();
    start->update();
    calculate->update();
    clear->update();
    for (int i = 0 ; i < 8 ; i++){
        textbox[i]->update();
        text[i]->update();
    }
    vel_gauge->setValue(squash->net_vel ,6);
    vel_gauge->update();
    x_gauge->setValue(squash->real_x ,6);
    x_gauge->update();
    y_gauge->setValue(squash->real_y ,6);
    y_gauge->update();
}

void ObjectManager::renderAllObject(){
    background->render();
    red->render();
    green->render();
    squash->render();
    vel_gauge->render();
    x_gauge->render();
    y_gauge->render();
    hoop->render();
    save->render();
    reset->render();
    start->render();
    calculate->render();
    clear->render();

    for (int i = 0 ; i < 6 ; i++){
        if (i == 2){
            textbox[i]->render();
            m_error->render();
            text[i]->render();
        }
        else if (i == 3){
            textbox[i]->render();
            xpos_error->render();
            text[i]->render();
        }
        else {
            textbox[i]->render();
            text[i]->render();
        }
    }
    textbox[6]->render();
    k_yellow->render();
    k_error->render();
    text[6]->render();
    textbox[7]->render();
    x_yellow->render();
    x_error->render();
    text[7]->render();

}

void ObjectManager::cleanAllObject(){
    background->clean();
    red->clean();
    green->clean();
    k_yellow->clean();
    x_yellow->clean();
    m_error->clean();
    xpos_error->clean();
    x_error->clean();
    k_error->clean();
    squash->clean();
    hoop->clean();
    save->clean();
    reset->clean();
    start->clean();
    calculate->clean();
    clear->clean();
    for (int i = 0 ; i < 8 ; i++){
        textbox[i]->clean();
        text[i]->clean();
    }
    vel_gauge->clean();
    x_gauge->clean();
    y_gauge->clean();
}

void ObjectManager::recallObject(){
    // do not call new object,it will cause memory leak (new = allocate memory)
    squash->reset();
    squash->setProjectile(last_height, last_vel, last_angle);
}

void ObjectManager::clearPanal(){
    //reset all input to "" and redraw 0 to screen
    for (int j = 0; j < 8; j++){
        if (j != 0 && j != 1 && j != 5){
            text[j]->in.clear();
            text[j]->redraw("0");
        }
    }
    //reset yellow block
    k_yellow->showTexture = false;
    x_yellow->showTexture = false;
    //reset block selected
    k_isSelected = false;
    x_isSelected = false;
}

void ObjectManager::textboxesDeselectExcept(int i){
    for (int j = 0; j < 8; j++){
        if (j == i){
            continue;
        }
        textbox[j]->isSelected = false;
        text[j]->isSelected = false;
    }
}

void ObjectManager::calculateProjectile(){
    if (text[2]->getValue() < 24){
        m_error->showTexture = true;
    }
    else if (text[3]->getValue() < 0.2){
        xpos_error->showTexture = true;
    }
    else if (text[6]->getValue() < 150 && k_isSelected){
        k_error->showTexture = true;
    }
    else if (text[7]->getValue() < 8 && x_isSelected){
        x_error->showTexture = true;
    }
    else if (text[6]->getValue() == 0 && text[7]->getValue() == 0){
        k_error->showTexture = true;
        x_error->showTexture = true;
    }
    else {
        float mass = text[2]->getValue()/1000;  //convert g to kg
        float s_x = text[3]->getValue();
        float s_y = text[4]->getValue()-0.537;
        float net_vel = sqrt((9.81 * pow(s_x, 2))/(2*pow(cos(45*M_PI/180), 2)*(tan(45*M_PI/180)*s_x - s_y)));
        //cout << "net_vel = " << net_vel << endl;

        float x = text[7]->getValue()/100;      //convert cm to m
        float k = text[6]->getValue();
        if (x_isSelected){
            if (x == 0){
                //Do nothing
            } else {
                float k1 = (mass*(pow(net_vel, 2) + 2*9.81*x*sin(45*M_PI/180))/pow(x, 2));
                //cout << "k1 = " << k1 << endl;
                text[6]->setValue(k1, 6);
            }
        }
        else if(k_isSelected){
            if (k == 0){
                //Do nothing
            } else {
                float x1 = find_x1(k/mass, -2*9.81*sin(45*M_PI/180), -pow(net_vel, 2));
                x1 = x1 * 100;
                //cout << "x1 = " << x1 << endl;
                text[7]->setValue(x1, 6);
            }
        }

        last_height = s_y;      //assign last height for recall
        last_vel = net_vel;     //assign last velocity for recall
        last_angle = 45;        //assign last angle for recall
        recallObject();         //reset projectile

        //update hoop texture and position
        hoop->showTexture = true;
        hoop->setPos(572 + (int)320*(text[3]->getValue()),326 + (int)320*(text[4]->getValue()-0.537));

        //allow file save
        allowSave = true;
        las_mass = text[2]->in;
        las_x = text[3]->in;
        las_y = text[4]->in;
        las_k = text[6]->in;
        las_spx = text[7]->in;
        vel_gauge->setValue(squash->net_vel ,6);
        las_vel = vel_gauge->in;
    }
}

void ObjectManager::saveToFile(){
    ofstream fout;
    fout.open("log.txt",ios::app);
    if (fout.is_open()){
        fout << "Log: Launcher_Info(x = 0 m, y = 0.537 m, mecha_mass = "<< las_mass <<" g) Target_Info(x = "<< las_x <<" m, y = "<< las_y <<" m) Spring_Info(k = "<< las_k <<" N/m, spring_x = "<< las_spx <<"cm) Projectile_Info(initial_vel = "<< las_vel <<" m/s, angle = 45 deg)"<< endl;
        fout.close();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Information", "Simulation Log was saved successfully in 'log.txt'", Game::window);
    }
    else{
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save Error", "Simulation Log could not be saved", Game::window);
    }
}
