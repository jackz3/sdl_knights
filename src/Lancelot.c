#include "Lancelot.h"
#include "EntityManager.h"
#include "Effect.h"
#include "GameState.h"
#include "util.h"
#include "ResourceManager.h"
#include "Sound.h"

// extern SDLApp *app;

static void actionCallback(void *charactor, const char *actionName, const char *actionParam);
static void actionStand(void **charactor)
{
  actionCallback(*charactor, "stand", NULL);
}
static void actionComboslash2(void **charactor)
{
  actionCallback(*charactor, "comboslash2", NULL);
}
static void actionComboslash3(void **charactor)
{
  actionCallback(*charactor, "comboslash3", NULL);
}
static void actionComboslash4(void **charactor)
{
  actionCallback(*charactor, "comboslash4", NULL);
}
static void actionComboslash5(void **charactor)
{
  actionCallback(*charactor, "comboslash5", NULL);
}
static void actionTired(void **charactor)
{
  actionCallback(*charactor, "tired", NULL);
}
static void actionWalkDefenseEnd(void **charactor)
{
  Lancelot *lancelot = (Lancelot *)*charactor;
  Sprite *sprite = lancelot->sprite;
  if (sprite->toward)
  {
    actionCallback(*charactor, "walk", "left");
  }
  else
  {
    actionCallback(*charactor, "walk", "right");
  }
}

static void actionCallback(void *charactor, const char *actionName, const char *actionParam)
{
  Lancelot *lancelot = (Lancelot *)charactor;
  Sprite *sprite = lancelot->sprite;
  if (strcmp(actionName, "walk") == 0)
  {
    if (strcmp(actionParam, "left") == 0 || strcmp(actionParam, "right") == 0)
    {
      lancelot->state = Lancelot_Walk;
      sprite->actionIndex = Sprite_GetActionId(sprite, "walk");
      sprite->loop = true;
      if (strcmp(actionParam, "left") == 0)
      {
        sprite->x -= lancelot->speed;
        sprite->toward = 1;
      }
      else if (strcmp(actionParam, "right") == 0)
      {
        sprite->x += lancelot->speed;
        sprite->toward = 0;
      }
    }
    else if (strcmp(actionParam, "up") == 0 || strcmp(actionParam, "down") == 0)
    {
      if (lancelot->state != Lancelot_Walkdefense)
      {
        lancelot->state = Lancelot_Walk;
        sprite->actionIndex = Sprite_GetActionId(sprite, "walk");
        sprite->loop = true;
      }
      if (strcmp(actionParam, "up") == 0)
      {
        sprite->y -= lancelot->speed / 2.5;
      }
      else if (strcmp(actionParam, "down") == 0)
      {
        sprite->y += lancelot->speed / 2.5;
      }
    }
  }
  if (strcmp(actionName, "stand") == 0)
  {
    lancelot->state = Lancelot_Stand;
    lancelot->sprite->actionIndex = Sprite_GetActionId(lancelot->sprite, "stand");
    lancelot->sprite->frameIndex = 0;
    lancelot->sprite->loop = false;
    lancelot->sprite->onEnd = NULL;
    lancelot->sprite->vx = 0;
    lancelot->comboFlag = 0;
  }
  /**
   * 动作,轻斩
   */
  if (strcmp(actionName, "lightslash") == 0)
  {
    Sound_Play(ResourceManager_GetSound("lightslash"), 0);
    sprite->actionIndex = Sprite_GetActionId(sprite, "lightslash");
    sprite->frameIndex = 0;
    sprite->loop = false;
    // sprite->onEnd = actionLogic.stand;
    Sprite_SetOnEnd(sprite, actionStand);
    lancelot->state = Lancelot_Lightslash;
    lancelot->attackPower = 2;
  }
  /**
   * 动作,连斩2
   */
  if (strcmp(actionName, "comboslash2") == 0)
  {
    Sound_Play(ResourceManager_GetSound("lightslash"), 0);
    sprite->actionIndex = Sprite_GetActionId(sprite, "comboslash2");
    sprite->frameIndex = 0;
    sprite->loop = false;
    Sprite_SetOnEnd(sprite, actionStand);
    lancelot->state = Lancelot_Comboslash2;
    lancelot->attackPower = 6;
  }
  /**
   * 动作,连斩3
   */
  if (strcmp(actionName, "comboslash3") == 0)
  {
    Sound_Play(ResourceManager_GetSound("lightslash"), 0);
    sprite->actionIndex = Sprite_GetActionId(sprite, "comboslash3");
    sprite->frameIndex = 0;
    sprite->loop = false;
    Sprite_SetOnEnd(sprite, actionStand);
    lancelot->state = Lancelot_Comboslash3;
    lancelot->attackPower = 8;
  }
  /**
   * 动作,连斩4
   */
  if (strcmp(actionName, "comboslash4") == 0)
  {
    Sound_Play(ResourceManager_GetSound("lightslash"), 0);
    sprite->actionIndex = Sprite_GetActionId(sprite, "comboslash4");
    sprite->frameIndex = 0;
    sprite->loop = false;
    Sprite_SetOnEnd(sprite, actionStand);
    lancelot->state = Lancelot_Comboslash4;
    lancelot->attackPower = 14;
  }
  /**
   * 动作,连斩5
   */
  if (strcmp(actionName, "comboslash5") == 0)
  {
    sprite->actionIndex = Sprite_GetActionId(sprite, "comboslash5");
    sprite->frameIndex = 0;
    sprite->loop = false;
    Sprite_SetOnEnd(sprite, actionComboslash4);
    lancelot->state = Lancelot_Comboslash5;
  }
  /**
   * 动作,连续斩
   */
  if (strcmp(actionName, "comboslash") == 0)
  {
    sprite->actionIndex = Sprite_GetActionId(sprite, "comboslash");
    sprite->frameIndex = 0;
    sprite->loop = false;
    Sprite_SetOnEnd(sprite, actionStand);
    lancelot->state = Lancelot_Comboslash;
  }
  /**
   * 动作,跳跃
   */
  if (strcmp(actionName, "jump") == 0)
  {
    lancelot->g = 0.292;
    lancelot->vz = -7;
    lancelot->state = Lancelot_Jump;
    sprite->actionIndex = Sprite_GetActionId(sprite, "jump");
    sprite->frameIndex = 0;
    sprite->loop = false;
  }
  /**
   * 动作,跳斩
   */
  if (strcmp(actionName, "jumpslash") == 0)
  {
    Sound_Play(ResourceManager_GetSound("doubleslash"), 0);
    lancelot->state = Lancelot_Jumpslash;
    sprite->actionIndex = Sprite_GetActionId(sprite, "jumpslash");
    sprite->frameIndex = 0;
    sprite->loop = false;
    lancelot->attackPower = 2;
  }
  /**
   * 动作,回身斩
   */
  if (strcmp(actionName, "backslash") == 0)
  {
    Sound_Play(ResourceManager_GetSound("lightslash"), 0);
    lancelot->state = Lancelot_Backslash;
    sprite->actionIndex = Sprite_GetActionId(sprite, "backslash");
    sprite->frameIndex = 0;
    sprite->loop = false;
    Sprite_SetOnEnd(sprite, actionStand);
    lancelot->attackPower = 10;
    //			prophetBomb();
  }
  /**
   * 动作,防御
   */
  if (strcmp(actionName, "defense") == 0)
  {
    lancelot->state = Lancelot_Defense;
    sprite->actionIndex = Sprite_GetActionId(sprite, "defense");
    sprite->frameIndex = 0;
    sprite->loop = false;
    Sprite_SetOnEnd(sprite, actionTired);
    sprite->flash = false;
    lancelot->flashLife = 0;
  }
  /**
   * 动作,疲劳
   */
  if (strcmp(actionName, "tired") == 0)
  {
    lancelot->state = Lancelot_Tired;
    sprite->actionIndex = Sprite_GetActionId(sprite, "tired");
    sprite->frameIndex = 0;
    sprite->loop = false;
    Sprite_SetOnEnd(sprite, actionStand);
  }
  /**
   * 动作,移动防御
   */
  if (strcmp(actionName, "walkdefense") == 0)
  {
    lancelot->state = Lancelot_Walkdefense;
    sprite->actionIndex = Sprite_GetActionId(sprite, "walkdefense");
    sprite->frameIndex = 0;
    sprite->frameCount = 0;
    sprite->loop = false;
    Sprite_SetOnEnd(sprite, actionWalkDefenseEnd);
    if (strcmp(actionParam, "left") == 0)
    {
      sprite->toward = 1;
    }
    else if (strcmp(actionParam, "right") == 0)
    {
      sprite->toward = 0;
    }
  }

}

void simulator(void **charactor)
{
  Lancelot *lancelot = (Lancelot *)*charactor;
  Sprite *sprite = lancelot->sprite;
  KeyState *keyState = SDLApp_GetKeyState();// &app->keyState;
  enum LancelotState state = lancelot->state;
  if (lancelot->z < 0)
  {
    static int i = 0;
    char name[16];
    sprintf(name, "effect1_%i", i++);
    Effect *effect = Effect_Create(name, lancelot->sprite->x, lancelot->sprite->y, "shadow", 2);
    effect->sprite->loop = true;
  }
  switch (state)
  {
  case Lancelot_Jump:
  case Lancelot_Jumpslash:
    if (keyState->left)
    {
      if (sprite->vx == 0)
      {
        sprite->vx = -lancelot->speed;
      }
      sprite->toward = true;
    }
    else if (keyState->right)
    {
      if (sprite->vx == 0)
      {
        sprite->vx = lancelot->speed;
      }
      sprite->toward = false;
    }
  case Lancelot_Kick:
  case Lancelot_Kickhit:
  case Lancelot_Retreatslash:
  case Lancelot_Wound3:
  case Lancelot_Wound4:
  case Lancelot_Die:
    if (state == Lancelot_Retreatslash)
    {
      sprite->vx = sprite->toward ? lancelot->speed : -lancelot->speed;
    }
    else if (state == Lancelot_Kick)
    {
      sprite->vx = sprite->toward ? -lancelot->speed / 2 : lancelot->speed / 2;
    }
    else if (state == Lancelot_Kickhit)
    {
      sprite->vx = sprite->toward ? lancelot->speed / 2 : -lancelot->speed / 2;
    }
    // jumpslash/kickhit产生的动作延迟
    if (lancelot->actionLogicCount > 0)
    {
      lancelot->actionLogicCount--;
      sprite->x -= sprite->vx;
    }
    else
    {
      lancelot->vz += lancelot->g;
      lancelot->z += lancelot->vz;
      sprite->x += sprite->vx;
    }
    if ((state == Lancelot_Wound4 || state == Lancelot_Die) && sprite->frameIndex == 10 && lancelot->fallCount == 2)
    {
      sprite->flash = true;
      lancelot->flashLife = 60;
      lancelot->z = 0;
      lancelot->vz = -5;
      sprite->vx = 1 * (sprite->toward ? -1 : 1);
      lancelot->fallCount++;
    }
    if (state == Lancelot_Die)
    {
      if (sprite->frameIndex == 4)
      {
        sprite->frameIndex = 6;
        sprite->frameCount = -1000;
      }
      if (sprite->frameIndex == 6)
      {
        sprite->frameCount = -1000;
      }
      if (sprite->frameIndex == 7 && lancelot->actionLogicCount < 1)
      {
        lancelot->actionLogicCount = 200;
      }
      if (sprite->frameIndex == 7 && lancelot->actionLogicCount == 175)
      {
        sprite->blink = true;
      }
      if (sprite->frameIndex == 7 && lancelot->actionLogicCount == 100)
      {
        sprite->blink = false;
        sprite->frameCount = 0;
        lancelot->z = 0;
        lancelot->vz = 0;
        // var life = stageManager.getLancelotLife();
        // if (life > 0){
        // 	stageManager.setLancelotLife(--life);
        // 	if (infoManager.lifeText){
        // 		infoManager.lifeText.set(life, 127 - life.toString().length * 8, 8, 100);
        // 	}
        // 	doAction('revert');
        // }else{
        // 	stageManager.goStage(0,5);
        // }
      }
    }
    if (lancelot->z > 0)
    {
      if (state == Lancelot_Wound3 && lancelot->flashLife > 0)
      {
        sprite->flash = 1;
      }
      if ((state == Lancelot_Wound4 || state == Lancelot_Die) && lancelot->fallCount < 3)
      {
        if (lancelot->fallCount == 0)
        {
          lancelot->fallCount++;
          sprite->frameIndex = 5;
          lancelot->z = 0;
          lancelot->vz = -3;
          // createDust();
        }
        else if (lancelot->fallCount == 1)
        {
          lancelot->fallCount++;
          lancelot->z = 0;
          lancelot->vz = 0;
          sprite->vx = 0;
          // createDust();
        }
        else if (lancelot->fallCount == 2)
        {
          lancelot->z = 0;
          lancelot->vz = 0;
          sprite->vx = 0;
          if (state == Lancelot_Die && sprite->frameIndex != 7)
          {
            sprite->frameIndex = 7;
            sprite->frameCount = -1000;
          }
        }
      }
      else
      {
        lancelot->z = 0;
        lancelot->vz = 0;
        sprite->vx = 0;
        actionCallback(lancelot, "stand", NULL);
        if (state != Lancelot_Kick)
        {
          Sound_Play(ResourceManager_GetSound("floor"), 0);
        }
        // createDust();
      }
    }
    sprite->sy = lancelot->z;
    break;
  }
  		/**
		 * 击中keeper
		 */
  LinkedList *keeperPool = GameState_GetKeeperPool();
  ItemNode* node = keeperPool->items;
  while(node) {
    char* name = (char*)node->item;
    Keeper* keeper = (Keeper*)EntityManager_GetCharactor(EntityManager_GetInstance(), name);
    if (keeper != NULL && collisionDetector(lancelot->sprite, (keeper)->sprite, 999, false, NULL)) {
        if (state != Lancelot_Powerslash || strcmp((keeper)->sprite->actions[(keeper)->sprite->actionIndex].name, "fence1") == 0) {
          Keeper_Unpack(keeper);
				}
			}
    node = node->next;
  }
}

Lancelot *Lancelot_Create(float x, float y, float health)
{
  Lancelot *lancelot = (Lancelot *)malloc(sizeof(Lancelot));
  strcpy(lancelot->name, "lancelot");
  strcpy(lancelot->actionName, "stand");
  lancelot->health = health;
  lancelot->healthMax = 80;
  lancelot->state = Lancelot_Stand;
  lancelot->speed = 2;
  lancelot->z = 0;
  lancelot->vz = 0;
  lancelot->g = 0.292;
  lancelot->controllState = Computer;
  lancelot->controllCount = 0;
  lancelot->actionLogicCount = 0;
  lancelot->actionID = 0;
  lancelot->beHitCount = 0;
  lancelot->flashLife = 0;
  lancelot->comboFlag = 0;
  lancelot->attackPower = 0;
  lancelot->fallCount = 0;
  lancelot->victory = false;
  // lancelot->victoryMask = 0;
  lancelot->lastHealth = lancelot->health;
  lancelot->feedbackDamage = true;
  lancelot->multiple = 1;
  // var keyMap = cfg.keyMap || {		//键盘操作配置
  // 	up: '87',
  // 	down: '83',
  // 	left: '65',
  // 	right: '68',
  // 	A: '74',
  // 	B: '75',
  // 	C: '76'
  // };
  // var lastHealth = health;

  EntityManager_CreateEntity(EntityManager_GetInstance(), lancelot->name, lancelot);
  Sprite *sprite = EntityManager_GetEntity(EntityManager_GetInstance(), lancelot->name);
  SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  Sprite_AddTexturedRectangle(sprite, SDLApp_GetRenderer(), "./assets/images/lancelot.png", rect);
  Sprite_SetPosition(sprite, x, y);
  Sprite_init(sprite, "./assets/lancelot.json");
  Sprite_SetActionCallBack(sprite, actionCallback);
  Sprite_SetSimulatorCallBack(sprite, simulator);
  sprite->actionIndex = Sprite_GetActionId(sprite, "stand");
  lancelot->sprite = sprite;
  printf("create lancelot\n");
  return lancelot;
}

void Lancelot_Destroy(Lancelot *lancelot)
{
  if (lancelot != NULL)
  {
    EntityManager_RemoveEntity(EntityManager_GetInstance(), lancelot->name);
    free(lancelot);
    printf("destroy lancelot\n");
  }
}

static void controller(Lancelot *lancelot)
{
  lancelot->controllCount++;
  if (lancelot->controllCount < 63)
  {
    actionCallback(lancelot, "walk", "right");
  }
  else if (lancelot->controllCount == 63)
  {
    actionCallback(lancelot, "stand", NULL);
  }
  else if (lancelot->controllCount == 125)
  {
    lancelot->controllState = Player;
    lancelot->controllCount = 0;
  }
}
void Lancelot_Controller(Lancelot *lancelot, KeyState *keyState)
{
  if (lancelot->controllState == Computer)
  {
    controller(lancelot);
    return;
  }
  bool stand = true;
  Sprite *sprite = lancelot->sprite;
  enum LancelotState state = lancelot->state;
  if (state == Lancelot_Tired)
    return;
  /**
   * 上下移动
   */
  if (keyState->up && (state == Lancelot_Stand || state == Lancelot_Walk || state == Lancelot_Walkdefense || state == Lancelot_Lightslash))
  {
    if (state == Lancelot_Lightslash && lancelot->sprite->frameIndex < 2 && keyState->up == 1)
    {
      Sprite_DoAction(sprite, lancelot, "kick", NULL);
    }
    else if (state != Lancelot_Lightslash)
    {
      Sprite_DoAction(sprite, lancelot, "walk", "up");
    }
    stand = false;
    keyState->up = 2;
  }
  if (keyState->down && (state == Lancelot_Stand || state == Lancelot_Walk || state == Lancelot_Walkdefense))
  {
    Sprite_DoAction(sprite, lancelot, "walk", "down");
    stand = false;
  }
  /**
   * 左右移动
   */
  if (keyState->left && (state == Lancelot_Stand || state == Lancelot_Walk || state == Lancelot_Walkdefense || state == Lancelot_Lightslash || state == Lancelot_Defense))
  {
    if (state == Lancelot_Lightslash && sprite->frameIndex < 2 && sprite->toward == 0)
    {
      actionCallback(lancelot, "defense", NULL);
    }
    else if (state == Lancelot_Lightslash && sprite->frameIndex < 2 && sprite->toward == 1 && keyState->left == 1)
    {
      actionCallback(lancelot, "heavyslash", NULL);
    }
    else if (sprite->toward == 0 && state != Lancelot_Defense)
    {
      actionCallback(lancelot, "walkdefense", "left");
    }
    else if (state == Lancelot_Stand || state == Lancelot_Walk)
    {
      actionCallback(lancelot, "walk", "left");
    }
    keyState->left = 2;
    stand = false;
  }
  else if (keyState->right && (state == Lancelot_Stand || state == Lancelot_Walk || state == Lancelot_Walkdefense || state == Lancelot_Lightslash || state == Lancelot_Defense))
  {
    if (state == Lancelot_Lightslash && sprite->frameIndex < 2 && sprite->toward == 1)
    {
      actionCallback(lancelot, "defense", NULL);
    }
    else if (state == Lancelot_Lightslash && sprite->frameIndex < 2 && sprite->toward == 0 && keyState->right == 1)
    {
      actionCallback(lancelot, "heavyslash", NULL);
    }
    else if (sprite->toward == 1 && state != Lancelot_Defense)
    {
      actionCallback(lancelot, "walkdefense", "right");
    }
    else if (state == Lancelot_Stand || state == Lancelot_Walk)
    {
      actionCallback(lancelot, "walk", "right");
    }
    keyState->right = 2;
    stand = false;
  }
  /**
   * 攻击
   */
  if (keyState->a == 1)
  {
    switch (state)
    {
    case Lancelot_Stand:
    case Lancelot_Walk:
      actionCallback(lancelot, "lightslash", NULL);
    case Lancelot_Lightslash:
    case Lancelot_Comboslash2:
    case Lancelot_Comboslash3:
    case Lancelot_Comboslash4:
    case Lancelot_Comboslash5:
      if (lancelot->comboFlag > 3)
      {
        lancelot->comboFlag = 0;
      }
      switch (lancelot->comboFlag)
      {
      case 1:
        if (sprite->toward && keyState->left == 1 || !sprite->toward && keyState->right == 1)
        {
          if (state != Lancelot_Comboslash5)
          {
            Sprite_SetOnEnd(sprite, actionComboslash5);
          }
          lancelot->comboFlag = 0;
        }
        else
        {
          if (state != Lancelot_Comboslash2)
          {
            Sprite_SetOnEnd(sprite, actionComboslash2);
          }
        }
        break;
      case 2:
        if (state != Lancelot_Comboslash3)
        {
          Sprite_SetOnEnd(sprite, actionComboslash3);
        }
        break;
      case 3:
        if (state != Lancelot_Comboslash4)
        {
          Sprite_SetOnEnd(sprite, actionComboslash4);
        }
        break;
      }
      stand = false;
      break;
    case Lancelot_Jump:
      actionCallback(lancelot, "jumpslash", NULL);
      stand = false;
      break;
    case Lancelot_Walkdefense:
      actionCallback(lancelot, "backslash", NULL);
      stand = false;
    }
    keyState->a = 2;
  }
  else if (keyState->a == 0 && state == Lancelot_Defense)
  {
    stand = true;
  }
  /**
   * 跳跃
   */
  if (keyState->b == 1 && (state != Lancelot_Jump && state != Lancelot_Jumpslash && state != Lancelot_Retreatslash))
  {
    if (state == Lancelot_Defense)
    {
      actionCallback(lancelot, "retreatslash", NULL);
    }
    else if (state == Lancelot_Lightslash && sprite->frameIndex < 2 && keyState->b == 1 && lancelot->health > 1)
    {
      actionCallback(lancelot, "powerslash", NULL);
    }
    else if (state == Lancelot_Stand || state == Lancelot_Walk || state == Lancelot_Walkdefense)
    {
      actionCallback(lancelot, "jump", NULL);
    }
    keyState->b = 2;
    stand = false;
  }

  /**
   * 恢复站立
   */
  if (stand && (state == Lancelot_Walk || state == Lancelot_Walkdefense || state == Lancelot_Defense))
  {
    actionCallback(lancelot, "stand", NULL);
  }
}