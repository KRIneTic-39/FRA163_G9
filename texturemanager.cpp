#include "texturemanager.h"

SDL_Texture* TextureManager::loadTexture(const char *fileName){
    SDL_Surface *tmpSurface = IMG_Load(fileName);   //load image to surface fixed
    if (tmpSurface == nullptr){
        SDL_Log("Failed to load texture from file : %s, %s", fileName, SDL_GetError());
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    if (tex == nullptr){
        SDL_Log("Failed to create texture from surface : %s", SDL_GetError());
    }

    SDL_FreeSurface(tmpSurface);    //clear surface
    tmpSurface = nullptr;

    return tex;
}

SDL_Texture* TextureManager::loadText(TTF_Font *font, const char *text, SDL_Color color){

    SDL_Surface *tmpSurface = TTF_RenderText_Solid(font, text, color);   //load solid text to surface
    if (tmpSurface == nullptr){
        SDL_Log("Failed to load text from font : %s", SDL_GetError());
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    if (tex == nullptr){
        SDL_Log("Failed to create text from surface : %s", SDL_GetError());
    }

    SDL_FreeSurface(tmpSurface);    //clear surface
    tmpSurface = nullptr;

    return tex;
}

void TextureManager::getPixels (SDL_Texture *op_tex, int *buf_width, int *buf_height){
    //cout << "TextureManager : get texture pixels" << endl;
    SDL_QueryTexture(op_tex, NULL, NULL, buf_width, buf_height);
}

void TextureManager::renderTex(SDL_Texture *op_tex, SDL_Rect sourceRec, SDL_Rect desRec){
    //first NULL for entire texture, second NULL for render to entire window
    SDL_RenderCopy(Game::renderer, op_tex, &sourceRec, &desRec);
}

void TextureManager::destroyTex(SDL_Texture *op_tex){   // reduce memory leak
    //cout << "TextureManager : destroy object texture" << endl;
    SDL_DestroyTexture(op_tex);
    op_tex = nullptr;
}

void TextureManager::destroyFont(TTF_Font *op_font){    // reduce memory leak
    //cout << "TextureManager : destroy object font" << endl;
    TTF_CloseFont(op_font);
    op_font = nullptr;
}


