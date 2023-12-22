#ifndef GameState_h
#define GameState_h
#include "util.h"
#include "Keeper.h"

typedef struct {
  LinkedList* keeperPool;
} GameState;

void GameState_Init();
void GameState_Destroy(GameState* gameState);
void GameState_AddKeeper(Keeper* keeper);
LinkedList* GameState_GetKeeperPool();

#endif