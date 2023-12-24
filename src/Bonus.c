#include "Bonus.h"
#include "sdl_app.h"
#include "EntityManager.h"

static void actionCallback(void *charactor, const char *actionName, const char *actionParam)
{
  Bonus *bonus = (Bonus *)charactor;
  if (strcmp(actionName, "stand") == 0)
  {
    bonus->sprite->actionIndex = Sprite_GetActionId(bonus->sprite, "stand");
  }
}

/**
 * 从箱子里发现物品
 */
static void discoverItem(Bonus *bonus)
{
  Sprite *sprite = bonus->sprite;
  const char *actionName = bonus->actionName;
  if (strcmp(actionName, "silverchest") == 0)
  {
    Bonus *b1 = Bonus_Create("silverbag1", sprite->x, sprite->y, "silverbag");
    b1->sprite->vx = 3;
    b1->sprite->vy = 0.5;
    Bonus *b2 = Bonus_Create("silverbag2", sprite->x, sprite->y, "silverbag");
    b2->sprite->vx = -3;
    b2->sprite->vy = -0.5;
    Bonus *b3 = Bonus_Create("silverbag3", sprite->x, sprite->y, "silverbag");
    b3->sprite->vx = 0;
    b3->sprite->vy = -1.5;
  }
  else if (strcmp(actionName, "goldchest") == 0)
  {
    Bonus *b1 = Bonus_Create("goldbag1", sprite->x, sprite->y, "goldbag");
    b1->sprite->vx = 3;
    b1->sprite->vy = 0.5;
    Bonus *b2 = Bonus_Create("goldbag2", sprite->x, sprite->y, "goldbag");
    b2->sprite->vx = -3;
    b2->sprite->vy = -0.5;
    Bonus *b3 = Bonus_Create("goldbag3", sprite->x, sprite->y, "goldbag");
    b3->sprite->vx = 0;
    b3->sprite->vy = -1.5;
  }
  else if (strcmp(actionName, "jewelrychest") == 0)
  {
    Bonus *bonus1 = Bonus_Create("jewelrybag1", sprite->x, sprite->y, "jewelrybag");
    bonus1->sprite->vx = 3.8;
    bonus1->sprite->vy = -0.95;
    Bonus *bonus2 = Bonus_Create("jewelrybag2", sprite->x, sprite->y, "jewelrybag");
    bonus2->sprite->vx = -2.2;
    bonus2->sprite->vy = -0.95;
    Bonus *bonus3 = Bonus_Create("jewelrybag3", sprite->x, sprite->y, "jewelrybag");
    bonus3->sprite->vx = 2.2;
    bonus3->sprite->vy = 0.95;
    Bonus *bonus4 = Bonus_Create("jewelrybag4", sprite->x, sprite->y, "jewelrybag");
    bonus4->sprite->vx = -3.8;
    bonus4->sprite->vy = 0.95;
  }
  else if (strcmp(actionName, "fruit") == 0)
  {
    Bonus *bonus1 = Bonus_Create("fruit1", sprite->x, sprite->y, "fruit-s1");
    bonus1->sprite->vx = 3.8;
    bonus1->sprite->vy = -0.95;
    Bonus *bonus2 = Bonus_Create("fruit2", sprite->x, sprite->y, "fruit-s2");
    bonus2->sprite->vx = -2.2;
    bonus2->sprite->vy = -0.95;
    Bonus *bonus3 = Bonus_Create("fruit3", sprite->x, sprite->y, "fruit-s1");
    bonus3->sprite->vx = 2.2;
    bonus3->sprite->vy = 0.95;
    Bonus *bonus4 = Bonus_Create("fruit4", sprite->x, sprite->y, "fruit-s1");
    bonus4->sprite->vx = -3.8;
    bonus4->sprite->vy = 0.95;
  }
  else if (strcmp(actionName, "bread") == 0)
  {
    Bonus *bonus1 = Bonus_Create("bread1", sprite->x, sprite->y, "bread-s");
    bonus1->sprite->vx = 2.5;
    bonus1->sprite->vy = 0;
    Bonus *bonus2 = Bonus_Create("bread2", sprite->x, sprite->y, "bread-s");
    bonus2->sprite->vx = -2.5;
    bonus2->sprite->vy = 0;
  }
  else if (strcmp(actionName, "ham") == 0)
  {
    Bonus *bonus1 = Bonus_Create("ham1", sprite->x, sprite->y, "ham-s");
    bonus1->sprite->vx = 3;
    bonus1->sprite->vy = 0.5;
    Bonus *bonus2 = Bonus_Create("ham2", sprite->x, sprite->y, "ham-s");
    bonus2->sprite->vx = -3;
    bonus2->sprite->vy = -0.5;
    Bonus *bonus3 = Bonus_Create("ham3", sprite->x, sprite->y, "ham-s");
    bonus3->sprite->vx = 0;
    bonus3->sprite->vy = -1.5;
  }
  else if (strcmp(actionName, "salad") == 0)
  {
    Bonus *bonus1 = Bonus_Create("salad1", sprite->x, sprite->y, "salad-s");
    bonus1->sprite->vx = 3.8;
    bonus1->sprite->vy = -0.95;
    Bonus *bonus2 = Bonus_Create("salad2", sprite->x, sprite->y, "salad-s");
    bonus2->sprite->vx = -2.2;
    bonus2->sprite->vy = -0.95;
    Bonus *bonus3 = Bonus_Create("salad3", sprite->x, sprite->y, "salad-s");
    bonus3->sprite->vx = 2.2;
    bonus3->sprite->vy = 0.95;
    Bonus *bonus4 = Bonus_Create("salad4", sprite->x, sprite->y, "salad-s");
    bonus4->sprite->vx = -3.8;
    bonus4->sprite->vy = 0.95;
  }
  else if (strcmp(actionName, "chicken") == 0)
  {
    Bonus *bonus1 = Bonus_Create("chicken1", sprite->x, sprite->y, "chicken-s");
    bonus1->sprite->vx = 3.8;
    bonus1->sprite->vy = -0.95;
    Bonus *bonus2 = Bonus_Create("chicken2", sprite->x, sprite->y, "chicken-s");
    bonus2->sprite->vx = -2.2;
    bonus2->sprite->vy = -0.95;
    Bonus *bonus3 = Bonus_Create("chicken3", sprite->x, sprite->y, "chicken-s");
    bonus3->sprite->vx = 2.2;
    bonus3->sprite->vy = 0.95;
    Bonus *bonus4 = Bonus_Create("chicken4", sprite->x, sprite->y, "chicken-s");
    bonus4->sprite->vx = -3.8;
    bonus4->sprite->vy = 0.95;
  }
}
	/**
	 * 修正越界，暂时用
	 */
static void	correctSpriteLocation(){
		// var r = stageManager.currentRegion;
		// if (x < r[0] + 50){
		// 	sprite.x = x = r[0] + 50;
		// }
		// if (y < r[1]){
		// 	sprite.y = y = r[1];
		// }
		// if (x > r[2] - 50){
		// 	sprite.x = x = r[2] - 50;
		// }
		// if (y > r[3]){
		// 	sprite.y = y = r[3];
		// }
	}
static void simulator(void **charactor)
{
  Bonus *bonus = (Bonus *)*charactor;
  switch (bonus->state)
  {
  case Bonus_Discover:
    if (bonus->actionLogicCount > 0)
    {
      // x = sprite.x;
      // y = sprite.y;
      bonus->actionLogicCount--;
    }
    else
    {
      bonus->sprite->ax = 0;
      bonus->sprite->ay = 0;
      bonus->sprite->vx = 0;
      bonus->sprite->vy = 0;
      bonus->state = Bonus_Stand;
    }
    break;
  case Bonus_Unpacking:
    if (bonus->actionLogicCount > 0)
    {
      bonus->actionLogicCount--;
    }
    else
    {
      discoverItem(bonus);
      Bonus_Destroy(bonus);
      *charactor = NULL;
    }
    break;
  case Bonus_GetBy:
    Bonus_Destroy(bonus);
    *charactor = NULL;
    break;
  }
  correctSpriteLocation();
}

Bonus *Bonus_Create(const char *name, float x, float y, const char *actionName)
{
  Bonus *bonus = malloc(sizeof(Bonus));
  strcpy(bonus->name, name);
  strcpy(bonus->actionName, actionName);
  bonus->actionLogicCount = 7;
  // var spriteID = 'bonus01';			//精灵资源id
  EntityManager_CreateEntity(EntityManager_GetInstance(), bonus->name, bonus);
  Sprite *sprite = EntityManager_GetEntity(EntityManager_GetInstance(), bonus->name);
  SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  Sprite_AddTexturedRectangle(sprite, SDLApp_GetRenderer(), "./assets/images/bonus01.png", rect);
  Sprite_SetPosition(sprite, x, y);

  Sprite_init(sprite, "./assets/bonus01.json");
  Sprite_SetActionCallBack(sprite, actionCallback);
  Sprite_SetSimulatorCallBack(sprite, simulator);
  sprite->actionIndex = Sprite_GetActionId(sprite, bonus->actionName);
  sprite->toward = false;
  sprite->loop = true;

  bonus->sprite = sprite;
  printf("created bonus: %s\n", bonus->name);
  return bonus;
}

void Bonus_Destroy(Bonus *bonus)
{
}