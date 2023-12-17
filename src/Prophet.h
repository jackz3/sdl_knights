#ifndef prophet_h
#define prophet_h

#include <SDL2/SDL.h>
#include "GameEntity.h"

enum state {
	Prophet_Stand,
	Prophet_prophet
};

typedef struct {
  float dx;
  float dy;
  char name[16]; 
  // char spriteID = 'prophet';			//精灵资源id
	float ax;			//ax加速度
	float ay;			//ay加速度
	float vx;			//vx速度
	float vy;			//vy速度
	float toward;		//精灵的方向
	// char state[16];				//有限状态机,表示角色当前的状态
	enum state state;
	char actionName[32];				//精灵当前动作
	float z;							//精灵z轴坐标
	float vz;							//精灵z轴速度
	float g;						//精灵重力加速度
  GameEntity* entity;
} Prophet;

Prophet* Prophet_Create(float x, float y);
void Prophet_Destroy(Prophet* prophet);
void simulatorCallBack(Prophet* prophet);
// void ball_render(Ball* ball);

#endif