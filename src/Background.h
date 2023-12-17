#ifndef Background_h
#define Background_h

#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h> // For Mac, use <SDL.h>
#include "TexturedRectangle.h"
#include "Collider.h"

typedef struct {
    float x;
    float y;
    int w;
    int h;
    TexturedRectangle* m_texture;
} BG;

BG* BG_Create(float x, float y, int w, int h);
void BG_Destroy(BG* bg);

void BG_Render(BG* entity);

// Adding Rectangle Components
void BG_AddTexture(BG* bg, SDL_Renderer* renderer, const char* path, const SDL_Rect* srcRect);

void BG_SetPosition(BG* bg, float x, float y);

#endif