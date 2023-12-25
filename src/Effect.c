#include "Effect.h"
#include "sdl_app.h"
#include "EntityManager.h"

static int id = 0;

void Effect_ActionCallback(void* charactor, const char* actionName, const char* actionParam) {

}

static void Effect_Simulator(void** charactor) {
  Effect* effect = (Effect*)*charactor;
  effect->life--;
  if (effect->life < 1){
    Effect_Destroy(effect);
    *charactor = NULL;
  }
  // offsetFunc(sprite, count++, instance);  
}

static Effect* _create(const char* spriteId, float x, float y, const char* actionName, int life, const char* cfg) {
  Effect* effect = (Effect*)malloc(sizeof(Effect));
  char name[16];
  sprintf(name, "%s-%i", spriteId, id++);
  strcpy(effect->name, name);
  strcpy(effect->actionName, actionName);
  effect->life = life;

  EntityManager_CreateEntity(EntityManager_GetInstance(), effect->name, effect);
  Sprite* sprite = EntityManager_GetEntity(EntityManager_GetInstance(), effect->name);
  SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  char path[128];
  sprintf(path, "./assets/images/%s.png", cfg);
  Sprite_AddTexturedRectangle(sprite, SDLApp_GetRenderer(), path, rect);
  Sprite_SetPosition(sprite, x, y);

  sprintf(path, "./assets/%s.json", cfg);
  Sprite_init(sprite, path);
  Sprite_SetActionCallBack(sprite, Effect_ActionCallback);
  Sprite_SetSimulatorCallBack(sprite, Effect_Simulator);
  sprite->actionIndex = Sprite_GetActionId(sprite, effect->actionName);
  sprite->toward = false;
  sprite->loop = true;
  
  effect->sprite = sprite;
  printf("created effect: %s\n", effect->name); 
  return effect;
}
Effect* Effect_Create(const char* spriteId, float x, float y, const char* actionName, int life) {
  return _create(spriteId, x, y, actionName, life, "effect1");
}

Effect* Effect_CreateNumber(const char* name, float x, float y, const char* actionName, int life, float sy, float vy) {
  Effect* effect = _create(name, x, y, actionName, life, "bonusNumber");
  effect->sprite->sy = sy;
  effect->sprite->vy = vy;
  return effect;
}

void Effect_Destroy(Effect* effect) {
  printf("destroying effect %s\n", effect->name);
  EntityManager_RemoveEntity(EntityManager_GetInstance(), effect->name);
  free(effect);
}
