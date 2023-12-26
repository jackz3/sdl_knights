#include "StageManager.h"
#include "Text.h"
#include "GameState.h"
#include "Background.h"

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

  BG_SetTexture(BG_Far, "./assets/images/stagex_1_b.png");
  Text *title = Text_Create("Disclaimer", 150, 30);
	Text *description = Text_Create("This program involved all the   material(including but not just pictures, animation, audio, etc.)were collected on the Internet.Copyright of the original game  belongs to the CAPCOM. This     program is for study and        research use, not allow used forany commercial purposes.", 62, 50);
  description->width = 32;
  GameState_AddText(title);
  GameState_AddText(description);
  return stage;
}