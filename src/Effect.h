#ifndef effect_h
#define effect_h

#include "Sprite.h"

typedef struct 
{
  char name[16];
  char spriteID[16];				//精灵资源id
	// var x = cfg.x;						//精灵x轴坐标
	// var y = cfg.y;						//精灵y轴坐标
	// bool toward;				//精灵的方向
	char actionName[16];	//精灵当前动作
	//以上是传给sprite构造器的参数
	// var controller = cfg.controller || function(){};
	int life;
	// float ax;			//ax加速度
	// float ay;			//ay加速度
	// float vx;			//vx速度
	// float vy;			//vy速度
	// float sx;			//x偏移量
	// float sy;			//y偏移量
	// bool loop;
	// bool blink;
	// var offsetFunc = cfg.offsetFunc || function(){};
  Sprite* sprite;
	int count;
} Effect;

Effect* Effect_Create(const char* spriteId, float x, float y, const char* actionName, int life);
void Effect_Destroy(Effect* effect);

// void simulatorCallBack(Effect* effect);

#endif