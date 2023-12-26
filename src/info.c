#include "Info.h"
#include "EntityManager.h"
#include "sdl_app.h"

static void actionCallback(void *charactor, const char *actionName, const char *actionParam) {

}

static void simulatorCallBack(void **charactor) {
  Info* info = (Info*)*charactor;
	info->life--;
		if (info->life < 1){
			Info_Destroy(info);
      *charactor = NULL;
		}
		// offsetFunc(sprite, count++, instance);
}

Info* Info_Create(char* name, float x, float y, float vx, float vy, bool toward, char* actionName, bool loop, int life) {
  Info* info = (Info*)malloc(sizeof(Info));
  strcpy(info->name, name);
  strcpy(info->actionName, actionName);
  info->count = 0;
  // info->state = Keeper_Stand;
  // info->actionLogicCount = 0;
  // info->lootsCount = 6;

  EntityManager_CreateEntity(EntityManager_GetInstance(), info->name, info);
  Sprite *sprite = EntityManager_GetEntity(EntityManager_GetInstance(), info->name);
  SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  Sprite_AddTexturedRectangle(sprite, SDLApp_GetRenderer(), "./assets/images/charactor.png", rect);
  Sprite_SetPosition(sprite, x, y);
  Sprite_init(sprite, "./assets/charactor.json");
  Sprite_SetActionCallBack(sprite, actionCallback);
  Sprite_SetSimulatorCallBack(sprite, simulatorCallBack);
  sprite->actionIndex = Sprite_GetActionId(sprite, actionName);
  sprite->ax = 0;
  sprite->ay = 0;
  sprite->vx = 0;
  sprite->vy = 0;
  sprite->sx = 0;
  sprite->sy = 0;
  sprite->loop = true;
  sprite->blink = false;
  sprite->toward = false;
  info->sprite = sprite;
  printf("create info\n");

}

void Info_Destroy(Info* info) {
  if (info->sprite != NULL)
  {
    EntityManager_RemoveEntity(EntityManager_GetInstance(), info->name);
  }
  free(info);
}