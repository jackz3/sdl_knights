#ifndef Sprite_h
#define Sprite_h

#include <stdbool.h>

typedef struct {
	char id[16]; 
	float left;
	float top;
	int width;
	int height;
} Frame;

typedef struct {
	Frame* frame;
	bool flip;
	int duration;
	float offsetX;
	float offsetY;
} ActionFrame;

typedef struct {
	Frame* frame;
	char name[16];
	char value[16];
	ActionFrame* actionFrames;
	int framesLen;
} Action;

typedef struct Sprite {
	int resourceID;				//对应的资源id
	Frame* frames;
	int framesLen;
	Action* actions;
	int actionsLen;
	float x;				//x坐标
	float y;				//y坐标
	float ax;			//ax加速度
	float ay;			//ay加速度
	float vx;			//vx速度
	float vy;			//vy速度
	float sx;			//sx偏移
	float sy;			//sy偏移
	int toward;	//方向
	int actionIndex;		//当前动作序号
	bool loop;				//动作是否循环
	bool blink; 					//是否闪烁
	bool blinkState; 		//当前闪烁状态
	bool display;

	int frameIndex;				//当前动作帧序号
	int frameCount; 			//记录当前duration
	bool flash; 					//是否闪烁
	bool flashState; 		//当前闪烁状态
	bool autoNextFrame;		//是否自动步进
	void (*simulatorCallBack)(void* charactor);
	void (*actionCallBack)(void* charactor, const char* actionName);
} Sprite;

Sprite* Sprite_Create();
void Sprite_init(Sprite* sprite, const char* fileName);
void Sprite_Destroy(Sprite* sprite);

void Sprite_NextFrame(Sprite* sprite, void* charactor);
void Sprite_nextActionFrame(Sprite* sprite);

void Sprite_SetSimulatorCallBack(Sprite* app, void (*func)(void*));
void Sprite_simulatorCallBack(Sprite* sprite, void* charactor);
void Sprite_SetActionCallBack(Sprite* sprite, void (*func)(void* charactor, const char* actionName));
void Sprite_DoAction(Sprite* sprite, void* charactor, const char* actionName);

#endif