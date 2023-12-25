#ifndef effect_h
#define effect_h

#include "Sprite.h"

typedef struct 
{
  char name[16];
  // char spriteID[16];				//精灵资源id
	char actionName[16];	//精灵当前动作
	// var controller = cfg.controller || function(){};
	int life;
	// var offsetFunc = cfg.offsetFunc || function(){};
  Sprite* sprite;
	int count;
} Effect;

Effect* Effect_Create(const char* spriteId, float x, float y, const char* actionName, int life);
void Effect_Destroy(Effect* effect);
Effect* Effect_CreateNumber(const char* name, float x, float y, const char* actionName, int life, float sy, float vy);

// void simulatorCallBack(Effect* effect);

#endif