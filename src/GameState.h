#ifndef GameState_h
#define GameState_h
#include "util.h"
#include "Keeper.h"
#include "Bonus.h"
#include "Text.h"

typedef struct {
  LinkedList* keeperPool;
  LinkedList* bonusPool;
  LinkedList* textPool;
  int lancelotHealth;
	int lancelotPoint;
	int lancelotLife;
} GameState;

void GameState_Init();
void GameState_Destroy(GameState* gameState);
void GameState_AddKeeper(Keeper* keeper);
LinkedList* GameState_GetKeeperPool();
void GameState_AddBonus(Bonus* keeper);
LinkedList* GameState_GetBonusPool();
void GameState_ClearBonusPool();
LinkedList* GameState_GetTextPool();
void GameState_AddText(Text* text);
void GameState_ClearTextPool();

int GameState_GetLancelotPoint();
int GameState_GetLancelotLife();
void GameState_SetLancelotPoint (int value);
void GameState_SetLancelotLife (int value);

#endif