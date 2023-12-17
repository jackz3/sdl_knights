#include "Background.h"
#include "config.h"


BG* BG_Create(float x, float y, int w, int h) {
  BG* bg = (BG*)malloc(sizeof(BG));
  bg->x = x;
  bg->y = y;
  bg->w = w;
  bg->h = h;
  bg->m_texture = NULL;
}

void BG_Destroy(BG* bg) {
  if (bg != NULL)
  {
    if (bg->m_texture != NULL) {
      TexturedRectangle_Destroy(bg->m_texture);
    }
    free(bg);
  }
}

void BG_Render(BG* bg) {
  if (bg->m_texture != NULL) {
    TexturedRectangle_Render(bg->m_texture, bg->x, bg->y, bg->w, bg->h);
  }
}

void BG_AddTexture(BG* bg, SDL_Renderer* renderer, const char* path, const SDL_Rect* srcRect) {
  if (bg->m_texture != NULL) {
      TexturedRectangle_Destroy(bg->m_texture);
  }
  SDL_Rect* rect = NULL;
  if (srcRect != NULL) {
    rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    memcpy(rect, srcRect, sizeof(SDL_Rect));
  }
  bg->m_texture = TexturedRectangle_Create(renderer, path, rect);
}

void BG_SetPosition(BG* bg, float x, float y) {
  if (bg->m_texture != NULL) {

  }
}