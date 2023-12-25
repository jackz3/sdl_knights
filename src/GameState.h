#ifndef GameState_h
#define GameState_h
#include "util.h"
#include "Keeper.h"
#include "Bonus.h"

typedef struct {
  LinkedList* keeperPool;
  LinkedList* bonusPool;
} GameState;

void GameState_Init();
void GameState_Destroy(GameState* gameState);
void GameState_AddKeeper(Keeper* keeper);
LinkedList* GameState_GetKeeperPool();
void GameState_AddBonus(Bonus* keeper);
LinkedList* GameState_GetBonusPool();
void GameState_ClearBonusPool();

#endif