#include "game.h"
#include "objectmanager.h"

SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;
InputManager Game::inputManager;
bool Game::renderText;

Game::Game(){}
Game::~Game(){}

void Game::init(const char *title,int x, int y, int w, int h){
    if (SDL_Init(SDL_INIT_VIDEO) == 0){
        //cout << "Game Initialized!..." << endl;

        window = SDL_CreateWindow(title, x, y, w, h, 0);                        //create window
        if (window){
            //cout << "Window Created!..." << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);    //create renderer
        if (renderer){
            SDL_SetRenderDrawColor(renderer,255, 255, 120, 255);
            //cout << "Renderer Created!..." << endl;
        }

        if(TTF_Init() == 0) {
            //cout << "TTF Initialized!..." << endl;
        }

        //disable text input
        SDL_StopTextInput();

        isRunning = true;

        //initialize GameObject here
        ObjectManager::initObject();
    }
    else{
        isRunning = false;
    }
}
void Game::handleEvents(){
    // SDL_PollEvent(&event) - Returns 1 if there is a pending event or 0 if there are none available
    // keep loop until there is no pending event left
    while (SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEMOTION:
            //sent mouse position to input manager
            inputManager.setMousePos(event.motion.x, event.motion.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            inputManager.pressKey(event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            inputManager.releaseKey(event.button.button);
            if (event.button.button == SDL_BUTTON_LEFT){
                ObjectManager::buttonHandle();
            }
            break;
        case SDL_KEYDOWN:
            inputManager.pressKey(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            inputManager.releaseKey(event.key.keysym.sym);
            for (int i = 0; i < 8; i++){
                if (text[i]->isSelected){
                    if (event.key.keysym.sym == SDLK_BACKSPACE && text[i]->in.size()){
                        text[i]->in.pop_back();
                        renderText = true;
                    }
                }
            }
            break;
        case SDL_TEXTINPUT:
            for (int i = 0; i < 8; i++){
                if (text[i]->isSelected){
                    //only number and dot can pass
                    if (((strcmp(event.text.text,"0") == 0) || (strcmp(event.text.text,"1") == 0) || (strcmp(event.text.text,"2") == 0) ||
                        (strcmp(event.text.text,"3") == 0) || (strcmp(event.text.text,"4") == 0) || (strcmp(event.text.text,"5") == 0) ||
                        (strcmp(event.text.text,"6") == 0) || (strcmp(event.text.text,"7") == 0) || (strcmp(event.text.text,"8") == 0) ||
                        (strcmp(event.text.text,"9") == 0) || (strcmp(event.text.text,".") == 0)) && text[i]->in.size() < text[i]->sizelimit)
                    {
                        // if found dot in string
                        if (text[i]->in.find('.') != std::string::npos){
                            if (strcmp(event.text.text,".") == 0){
                                //Do nothing
                            }
                            else {
                                text[i]->in += event.text.text;
                                renderText = true;
                            }
                        }
                        // if no dot in string
                        else {
                            text[i]->in += event.text.text;
                            renderText = true;
                        }
                    }
                }
            }
            break;
        default:
            break;
        };
    }
    /*
    if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
        inputManager.printMousePos(); //print mouse position when press left button
    }*/
}
void Game::update(){
    //u_count++;

    ObjectManager::updateAllObject();

    //cout << "Update Count: "<<  u_count << endl;
}
void Game::render(){
    //clear canvas for new image
    SDL_RenderClear(renderer);

    //this is where we add stuff to render
    ObjectManager::renderAllObject();

    //update screen
    SDL_RenderPresent(renderer);

    //add stuff after render
    if (x_error->showTexture && k_error->showTexture){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Information", "Either spring parameter 'k' or 'x' must be entered to Calculate", Game::window);
        x_error->showTexture = false;
        k_error->showTexture = false;
    }
    else if (m_error->showTexture){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Invalid Parameter Value", "Mechanism Parameter: 'm' must be entered from 24 to 600 g", Game::window);
        m_error->showTexture = false;
    }
    else if (xpos_error->showTexture){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Invalid Parameter Value", "Target Parameter: 'X' must be entered from 0.2 to 2.1 m", Game::window);
        xpos_error->showTexture = false;
    }
    else if (k_error->showTexture){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Invalid Parameter Value", "Spring Parameter: 'k' must be entered from 150.0 to 2000.0 N/m", Game::window);
        k_error->showTexture = false;
    }
    else if (x_error->showTexture){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Invalid Parameter Value", "Spring Parameter: 'x' must be entered from 8.0 to 32.0 cm", Game::window);
        x_error->showTexture = false;
    }
}
void Game::clean(){
    ObjectManager::cleanAllObject();

    SDL_StopTextInput();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = nullptr;
    renderer = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    //cout << "Game Cleaned!..." << endl;
}
