#ifndef Info_h
#define Info_h
#include <stdbool.h>
#include "Sprite.h"

typedef struct {
  char name[16];
	char actionName[32];
	int life; 
	bool loop;
	bool blink;
	Sprite* sprite;							//精灵实例
	int count;
  //  = cfg.life || 10;
  // = cfg.loop || true;
  // = cfg.blink || 0;
  //count  = 0;
} Info;

Info* Info_Create(char* name, float x, float y, float vx, float vy, bool toward, char* actionName, bool loop, int life);
void Info_Destroy(Info* info);

#endif