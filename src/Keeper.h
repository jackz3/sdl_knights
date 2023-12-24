#ifndef Keeper_h
#define Keeper_h

#include <SDL2/SDL.h>
#include "Sprite.h"

enum Keeper_State {
	Keeper_Stand,
	Keeper_Upacking
};

typedef struct {
  char name[16];
	enum Keeper_State state;
	char actionName[32];				//精灵当前动作
  int actionLogicCount;
	Sprite* sprite;
	char loots[10][16];
	int lootsCount;
} Keeper;

Keeper* Keeper_Create(float x, float y, const char* actionName, const char* loot, const char* name);
void Keeper_Destroy(Keeper* keeper);
void Keeper_Unpack(Keeper* keeper);

#endif