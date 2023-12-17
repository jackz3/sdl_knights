#include "Effect.h"
#include "sdl_app.h"

extern SDLApp* app;

void Effect_ActionCallback(void* charactor, const char* actionName) {

}

void Effect_Simulator(void* charactor) {
  Effect* effect = (Effect*)charactor;
  effect->life--;
  if (effect->life < 1){
    Effect_Destroy(effect);
  }
  // offsetFunc(sprite, count++, instance);  
}

Effect* Effect_Create(float x, float y) {
  Effect* effect = (Effect*)malloc(sizeof(Effect));
  strcpy(effect->name, "effect");
  effect->life = 10;
  effect->loop = true;

  EntityManager_CreateEntity(EntityManager_GetInstance(), effect->name);
  GameEntity* entity = EntityManager_GetEntityRef(EntityManager_GetInstance(), effect->name);
  SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  GameEntity_AddTexturedRectangleComponent(entity, app->renderer, "./assets/images/effect1.png", rect);
  GameEntity_SetPosition(entity, x, y);

  Sprite* sprite = Sprite_Create();
  GameEntity_AddSprite(entity, sprite);
  Sprite_init(sprite, "./assets/effect1.json");
  Sprite_SetActionCallBack(sprite, Effect_ActionCallback);
  Sprite_SetSimulatorCallBack(sprite, Effect_Simulator);
  effect->entity = entity;
  printf("create prophet\n"); 
  return effect;

}

void Effect_Destroy(Effect* effect) {
  if (effect->entity != NULL) {
    GameEntity_Destroy(effect->entity);
  }
  free(effect);
}

void simulatorCallBack(Effect* effect) {

}