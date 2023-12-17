#ifndef TEXTUREDRECTANGLE_H
#define TEXTUREDRECTANGLE_H

#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

typedef struct {
    SDL_Texture* texture;
    SDL_Rect* srcRect;
    int redColorKey;
    int greenColorKey;
    int blueColorKey;
    SDL_Renderer* m_renderer;
} TexturedRectangle;

TexturedRectangle* TexturedRectangle_Create(SDL_Renderer* renderer, const char* filepath, SDL_Rect* srcRect);
TexturedRectangle* TexturedRectangle_CreateWithColorKey(SDL_Renderer* renderer, const char* filepath, SDL_Rect* srcRect, int redColorKey, int greenColorKey, int blueColorKey);
void TexturedRectangle_InitDefaults(TexturedRectangle* rectangle);
void TexturedRectangle_Destroy(TexturedRectangle* rectangle);
SDL_Texture* TexturedRectangle_GetSDLTexture(TexturedRectangle* rectangle);
int TexturedRectangle_GetRedColorKey(TexturedRectangle* rectangle);
int TexturedRectangle_GetGreenColorKey(TexturedRectangle* rectangle);
int TexturedRectangle_GetBlueColorKey(TexturedRectangle* rectangle);
void TexturedRectangle_Update(TexturedRectangle* rectangle);
void TexturedRectangle_Render(TexturedRectangle* rectangle, float x, float y, int w, int h);
void TexturedRectangle_SetSrcPosition(TexturedRectangle* rectangle, float x, float y);
void TexturedRectangle_SetSrcDimension(TexturedRectangle* rectangle, int w, int h);


#endif
