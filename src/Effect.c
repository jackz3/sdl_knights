#include "Effect.h"
#include "sdl_app.h"
#include "EntityManager.h"

extern SDLApp* app;

void Effect_ActionCallback(void* charactor, const char* actionName) {

}

static void Effect_Simulator(void* charactor) {
  Effect* effect = (Effect*)charactor;
  effect->life--;
  if (effect->life < 1){
    Effect_Destroy(effect);
  }
  // offsetFunc(sprite, count++, instance);  
}

Effect* Effect_Create(const char* spriteId, float x, float y, bool toward, const char* actionName, int life) {
  Effect* effect = (Effect*)malloc(sizeof(Effect));
  strcpy(effect->name, spriteId);
  strcpy(effect->spriteID, spriteId);
  strcpy(effect->actionName, actionName);
  effect->toward = toward;
  effect->life = life;
  effect->loop = true;

  EntityManager_CreateEntity(EntityManager_GetInstance(), effect->spriteID, effect);
  Sprite* sprite = EntityManager_GetEntity(EntityManager_GetInstance(), effect->spriteID);
  SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  Sprite_AddTexturedRectangle(sprite, app->renderer, "./assets/images/effect1.png", rect);
  Sprite_SetPosition(sprite, x, y);

  Sprite_init(sprite, "./assets/effect1.json");
  Sprite_SetActionCallBack(sprite, Effect_ActionCallback);
  Sprite_SetSimulatorCallBack(sprite, Effect_Simulator);
  sprite->actionIndex = Sprite_GetActionId(sprite, effect->actionName);
  effect->sprite = sprite;
  printf("create effect\n"); 
  return effect;
}

void Effect_Destroy(Effect* effect) {
  if (effect->sprite != NULL) {
    Sprite_Destroy(effect->sprite);
  }
  free(effect);
}
