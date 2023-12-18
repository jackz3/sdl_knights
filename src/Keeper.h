#ifndef Keeper_h
#define Keeper_h

#include <SDL2/SDL.h>
#include "Sprite.h"

enum state {
	Keeper_Stand,
	Prophet_prophet
};

typedef struct {
  char spriteId[16];
	float toward;		//精灵的方向
	// char state[16];				//有限状态机,表示角色当前的状态
	enum state state;
	char actionName[32];				//精灵当前动作
  int actionLogicCount;
	Sprite* entity;
	// var loot = (cfg.loot || 'goldchest,silverchest,jewelrybag,silverbag,goldbag,jewelrychest').split(',');
} Keeper;

Keeper* Keeper_Create(float x, float y);
void Keeper_Destroy(Keeper* keeper);
void simulatorCallBack(Keeper* keeper);

#endif