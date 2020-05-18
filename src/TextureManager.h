#ifndef TEXTUREMANAGER.H
#define TEXTUREMANAGER.H


#include "./Game.h"

class TextureManager {
    public:
        static SDL_Texture* LoadTexture(const char* fileName); // Will return a SDL_Texture
        static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip); //SDL_Texture* is a pointer to SDL_Texture

};

#endif