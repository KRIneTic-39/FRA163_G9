#include "game.h"

class TextureManager{
public:
    static SDL_Texture *loadTexture(const char *fileName);
    static SDL_Texture *loadText(TTF_Font *font, const char *text, SDL_Color color);
    static void getPixels (SDL_Texture *op_tex, int *buf_width, int *buf_height);
    static void renderTex(SDL_Texture *op_tex, SDL_Rect sourceRec, SDL_Rect desRec);
    static void destroyTex(SDL_Texture *op_tex);
    static void destroyFont(TTF_Font *op_font);
};
