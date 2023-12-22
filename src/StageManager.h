#ifndef StageManager_h
#define StageManager_h

#include <SDL2/SDL.h>

typedef struct Stage 
{
  char name[16];
	void (*handelInput)(SDL_Event* event, const Uint8* keysState);
  void (*update)(Uint32 delta);
  void (*render)();
  void (*destroy)(struct Stage* stage);
} Stage;

typedef struct {
  Stage* current;

} StageManager;

void StageManager_Init();
void Stage_Change(Stage* stage);
void Stage_HandleInput(SDL_Event* event, const Uint8* keysState);
void Stage_Update(Uint32 delta);
void Stage_Render();

Stage* Stage_Create_0(const char* name);

Stage* Stage_Create_1(const char* name);

#endif