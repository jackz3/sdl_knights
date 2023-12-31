#include <stdlib.h>
#include <stdio.h>
#include "TexturedRectangle.h"
#include "ResourceManager.h"

TexturedRectangle* TexturedRectangle_Create(SDL_Renderer* renderer, const char* filepath, SDL_Rect* srcRect) {
    return TexturedRectangle_CreateWithColorKey(renderer, filepath, srcRect, 0x00, 0x00, 0x00);
}

TexturedRectangle* TexturedRectangle_CreateWithColorKey(SDL_Renderer* renderer, const char* filepath, SDL_Rect* srcRect, int redColorKey, int greenColorKey, int blueColorKey) {
    TexturedRectangle* rectangle = (TexturedRectangle*)malloc(sizeof(TexturedRectangle));
    if (rectangle == NULL) {
        printf("Failed to allocate memory for TexturedRectangle.\n");
        return NULL;
    }
    rectangle->m_renderer = renderer;
    // SDL_Rect* rect = malloc(sizeof(SDL_Rect));
    // memcpy(rect, &srcRect, sizeof(SDL_Rect));
    rectangle->srcRect = srcRect;
    SDL_Surface* retrieveSurface = ResourceManager_GetSurface(filepath);
    // SDL_SetColorKey(retrieveSurface, SDL_TRUE, SDL_MapRGB(retrieveSurface->format, redColorKey, greenColorKey, blueColorKey));
    rectangle->texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);

    TexturedRectangle_InitDefaults(rectangle);

    rectangle->redColorKey = redColorKey;
    rectangle->greenColorKey = greenColorKey;
    rectangle->blueColorKey = blueColorKey;
    return rectangle;
}

void TexturedRectangle_InitDefaults(TexturedRectangle* rectangle) {
    rectangle->redColorKey = 0xFF;
    rectangle->greenColorKey = 0x00;
    rectangle->blueColorKey = 0xFF;
}

void TexturedRectangle_Destroy(TexturedRectangle* rectangle) {
    if (rectangle != NULL) {
        if (rectangle->srcRect != NULL) {
            free(rectangle->srcRect);
        }
        SDL_DestroyTexture(rectangle->texture);
        free(rectangle);
    }
}

SDL_Texture* TexturedRectangle_GetSDLTexture(TexturedRectangle* rectangle) {
    return rectangle->texture;
}

int TexturedRectangle_GetRedColorKey(TexturedRectangle* rectangle) {
    return rectangle->redColorKey;
}

int TexturedRectangle_GetGreenColorKey(TexturedRectangle* rectangle) {
    return rectangle->greenColorKey;
}

int TexturedRectangle_GetBlueColorKey(TexturedRectangle* rectangle) {
    return rectangle->blueColorKey;
}

void TexturedRectangle_Update(TexturedRectangle* rectangle) {
    // Do update logic here
}

void TexturedRectangle_Render(TexturedRectangle* rectangle, float x, float y, int w, int h) {
    SDL_Rect rect = {
        x, y, w, h
    };
    SDL_RenderCopy(rectangle->m_renderer, rectangle->texture, rectangle->srcRect, &rect);
}

void TexturedRectangle_RenderEx(TexturedRectangle* rectangle, float x, float y, int w, int h, SDL_RendererFlip flip) {
    SDL_Rect rect = {
        x, y, w, h
    };
    SDL_RenderCopyEx(rectangle->m_renderer, rectangle->texture, rectangle->srcRect, &rect, 0, NULL, flip);
}

void TexturedRectangle_SetSrcPosition(TexturedRectangle* rectangle, float x, float y) {
    rectangle->srcRect->x = x;
    rectangle->srcRect->y = y;
}
void TexturedRectangle_SetSrcDimension(TexturedRectangle* rectangle, int w, int h) {
    rectangle->srcRect->w = w;
    rectangle->srcRect->h = h;
}
