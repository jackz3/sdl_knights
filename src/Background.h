#ifndef Background_h
#define Background_h

#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h> // For Mac, use <SDL.h>
#include "TexturedRectangle.h"

enum BG_Type {
    BG_Far,
    BG_Mid,
    BG_Fore
};

typedef struct {
    float x;
    float y;
    int w;
    int h;
    TexturedRectangle* textureFar;
    TexturedRectangle* textureMid;
    TexturedRectangle* textureFore;
} BG;

void BG_Init();
void BG_Destroy();

void BG_RenderFar();
void BG_RenderMid();
void BG_RenderFore();

void BG_SetTexture(enum BG_Type type, const char* path);

void BG_SetPosition(float x, float y);

#endif