#ifndef prophet_h
#define prophet_h

#include <SDL2/SDL.h>
#include "Sprite.h"

enum state {
	Prophet_Stand,
	Prophet_prophet
};

typedef struct {
  float dx;
  float dy;
  char name[16]; 
	enum state state;
	char actionName[32];				//精灵当前动作
	float z;							//精灵z轴坐标
	float vz;							//精灵z轴速度
	float g;						//精灵重力加速度
  Sprite* sprite;
} Prophet;

Prophet* Prophet_Create(float x, float y);
void Prophet_Destroy(Prophet* prophet);

#endif