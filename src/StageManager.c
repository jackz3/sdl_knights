#include "StageManager.h"

static StageManager* stageMgr;

void StageManager_Init() {
  stageMgr = (StageManager*)malloc(sizeof(StageManager));
  Stage* stage = Stage_Create_0("title");
  stageMgr->current = stage;
} 

void Stage_Change(Stage* stage) {
  stageMgr->current->destroy(stageMgr->current);
  stageMgr->current = stage;
}

void Stage_HandleInput(SDL_Event* event, const Uint8* keysState) {
  stageMgr->current->handelInput(event, keysState);
}
void Stage_Update(Uint32 delta) {
  stageMgr->current->update(delta);
}
void Stage_Render() {
  stageMgr->current->render();
}

static void stage0HandleInput (SDL_Event* event, const Uint8* keysState) {
  if (event->type == SDL_KEYDOWN) {
    printf("key down\n");
    if (event->key.keysym.sym == SDLK_RETURN) {
      Stage* stage = Stage_Create_1("game"); 
      Stage_Change(stage);
    }
  }
}

static void stage0Update (Uint32 delta) {
   
}
static void stage0Render() {

}
static void stage0Destroy (Stage* stage) {
  free(stage);
}

Stage* Stage_Create_0(const char* name) {
  Stage* stage = (Stage*)malloc(sizeof(Stage));
  strncpy(stage->name, name, sizeof(stage->name) - 1);
  stage->name[sizeof(stage->name) - 1] = '\0';
  stage->handelInput = stage0HandleInput;
  stage->update = stage0Update;
  stage->render = stage0Render;
  stage->destroy= stage0Destroy;
  return stage;
}