#include "Keeper.h"
#include "sdl_app.h"
#include "EntityManager.h"
#include "Effect.h"

extern SDLApp *app;

static void actionCallback(void *charactor, const char *actionName, const char *actionParam)
{
  Keeper *keeper = (Keeper *)charactor;
  if (strcmp(actionName, "stand") == 0)
  {
    keeper->state = Keeper_Stand;
    keeper->sprite->actionIndex = Sprite_GetActionId(keeper->sprite, actionName);
  }
  else if (strcmp(actionName, "unpacking") == 0)
  {
    char *an = keeper->actionName;
    if (strcmp(an, "cask") == 0)
    {
      keeper->state = Keeper_Upacking;
      keeper->sprite->actionIndex = Sprite_GetActionId(keeper->sprite, "cask-b");
      keeper->actionLogicCount = 25;
      keeper->sprite->blink = true;
      // soundManager.play('cask');
      Effect *effect = Effect_Create("effect1_cask", keeper->sprite->x, keeper->sprite->y, "cask", 8);
      effect->sprite->sy = -50;
      Effect *effectChip1 = Effect_Create("effect1_chip1", keeper->sprite->x, keeper->sprite->y, "chip1", 28);
      effectChip1->sprite->sy = -45;
      effectChip1->sprite->sx = -10;
      effectChip1->sprite->ay = 0.1;
      effectChip1->sprite->vy = -0.9;
      effectChip1->sprite->vx = -0.8;
      Effect *effectChip2 = Effect_Create("effect1_chip2", keeper->sprite->x, keeper->sprite->y, "chip2", 28);
      effectChip2->sprite->sy = -45;
      effectChip2->sprite->sx = 10;
      effectChip2->sprite->ay = 0.1;
      effectChip2->sprite->vy = -0.9;
      effectChip2->sprite->vx = 0.8;
      Effect *effectChip3 = Effect_Create("effect1_chip3", keeper->sprite->x, keeper->sprite->y, "chip3", 28);
      effectChip3->sprite->sy = -35;
      effectChip3->sprite->sx = -10;
      effectChip3->sprite->ay = 0.1;
      effectChip3->sprite->vy = -0.3;
      effectChip3->sprite->vx = -0.8;
      Effect *effectChip4 = Effect_Create("effect1_chip4", keeper->sprite->x, keeper->sprite->y, "chip4", 28);
      effectChip4->sprite->sy = -35;
      effectChip4->sprite->sx = 10;
      effectChip4->sprite->ay = 0.1;
      effectChip4->sprite->vx = 0.8;
      effectChip4->sprite->vy = -0.3;
      // new Bonus({
      // 	x: x,
      // 	y: y - 2,
      // 	actionLogicCount: 20,
      // 	actionName: loot[Math.floor(Math.random() * loot.length)]
      // });
    }
    else if (strcmp(an, "fence1") == 0 || strcmp(an, "fence2") == 0)
    {
      keeper->state = Keeper_Upacking;
      keeper->sprite->actionIndex = Sprite_GetActionId(keeper->sprite, "fence1-b");
      keeper->actionLogicCount = 25;
      keeper->sprite->blink = true;
      // soundManager.play('cask');
      Effect *effect = Effect_Create("effect1_chop", keeper->sprite->x, keeper->sprite->y, "chopflash", 8);
      effect->sprite->sy = -50;
      // new Bonus({
      // 	x: x,
      // 	y: y,
      // 	actionLogicCount: 45,
      // 	actionName: loot[Math.floor(Math.random() * loot.length)]
      // });
    }
  }
}

static void simulatorCallBack(void **charactor)
{
  Keeper *keeper = (Keeper *)*charactor;
  if (keeper->state == Keeper_Upacking)
  {
    if (keeper->actionLogicCount > 0)
    {
      keeper->actionLogicCount--;
    }
    else
    {
      Keeper_Destroy(keeper);
      *charactor = NULL;
    }
  }
}

Keeper *Keeper_Create(float x, float y, const char *actionName, const char *loot, const char* name)
{
  Keeper *keeper = (Keeper *)malloc(sizeof(Keeper));
  strcpy(keeper->name, name);
  strcpy(keeper->actionName, actionName);
  keeper->state = Keeper_Stand;
  keeper->actionLogicCount = 0;

  EntityManager_CreateEntity(EntityManager_GetInstance(), keeper->name, keeper);
  Sprite *sprite = EntityManager_GetEntity(EntityManager_GetInstance(), keeper->name);
  SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  Sprite_AddTexturedRectangle(sprite, app->renderer, "./assets/images/keeper01.png", rect);
  Sprite_SetPosition(sprite, x, y);
  Sprite_init(sprite, "./assets/keeper01.json");
  Sprite_SetActionCallBack(sprite, actionCallback);
  Sprite_SetSimulatorCallBack(sprite, simulatorCallBack);
  sprite->actionIndex = Sprite_GetActionId(sprite, actionName);
  sprite->ax = 0;
  sprite->ay = 0;
  sprite->vx = 0;
  sprite->vy = 0;
  sprite->loop = false;
  sprite->toward = false;
  keeper->sprite = sprite;
  // var spriteID = cfg.spriteID;				//精灵资源id
  printf("create prophet\n");
  return keeper;
}

void Keeper_Destroy(Keeper *keeper)
{
  if (keeper->sprite != NULL)
  {
    EntityManager_RemoveEntity(EntityManager_GetInstance(), keeper->name);
  }
  free(keeper);
}

void Keeper_Unpack(Keeper *keeper)
{
  if (keeper->state == Keeper_Stand)
  {
    actionCallback(keeper, "unpacking", NULL);
  }
}