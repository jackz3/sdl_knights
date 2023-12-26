#include "Background.h"
#include "config.h"
#include "sdl_app.h"
#include "camera.h"

static BG* bg = NULL;

void BG_Init(int w, int h) {
  bg = (BG*)malloc(sizeof(BG));
  bg->x = 0;
  bg->y = 0;
  bg->w = VIRTUALWIDTH;
  bg->h = VIRTUALHEIGHT;
  bg->textureFar = NULL;
  bg->textureMid = NULL;
  bg->textureFore = NULL;
}

void BG_Destroy(BG* bg) {
    if (bg->textureFar != NULL) {
      TexturedRectangle_Destroy(bg->textureFar);
    }
    if (bg->textureMid != NULL) {
      TexturedRectangle_Destroy(bg->textureMid);
    }
    if (bg->textureFore != NULL) {
      TexturedRectangle_Destroy(bg->textureFore);
    }
    free(bg);
}

void BG_RenderFar() {
  if (bg->textureFar != NULL) {
    Camera_Adjust();
    float sx = Camera_GetX() * 0.7;
    TexturedRectangle_SetSrcPosition(bg->textureFar, sx, 0);
    TexturedRectangle_Render(bg->textureFar, bg->x, bg->y, bg->w, bg->h);
  }
}
void BG_RenderMid() {
  if (bg->textureMid != NULL) {
    Camera_Adjust();
    TexturedRectangle_SetSrcPosition(bg->textureMid, Camera_GetX(), 0);
    TexturedRectangle_Render(bg->textureMid, bg->x, bg->y, bg->w, bg->h);
  }
}
void BG_RenderFore() {
  if (bg->textureFore != NULL) {
    Camera_Adjust();
    TexturedRectangle_SetSrcPosition(bg->textureFore, Camera_GetX(), 0);
    TexturedRectangle_Render(bg->textureFore, bg->x, bg->y, bg->w, bg->h);
  }
}

void BG_SetTexture(enum BG_Type type, const char* path) {
  SDL_Renderer* renderer = SDLApp_GetRenderer();
  SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  rect->x = 0;
  rect->y = 0;
  rect->w = bg->w;
  rect->h = bg->h;

  switch (type)
  {
  case BG_Far:
    if (bg->textureFar != NULL) {
      TexturedRectangle_Destroy(bg->textureFar);
    }
    bg->textureFar = TexturedRectangle_Create(renderer, path, rect);
    break;
  case BG_Mid:
    if (bg->textureMid != NULL) {
      TexturedRectangle_Destroy(bg->textureMid);
    }
    bg->textureMid = TexturedRectangle_Create(renderer, path, rect);
    break;
  case BG_Fore:
    if (bg->textureFore != NULL) {
      TexturedRectangle_Destroy(bg->textureFore);
    }
    bg->textureFore = TexturedRectangle_Create(renderer, path, rect);
    break; 
  }
}

void BG_SetPosition(float x, float y) {
}