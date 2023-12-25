#include "GameState.h"

static GameState* gameState;

void GameState_Init() {
  gameState = (GameState*)malloc(sizeof(GameState));
  gameState->keeperPool = LinkedList_Create();
  gameState->bonusPool = LinkedList_Create();
}
void GameState_Destroy(GameState* gameState) {
  free(gameState);
}

void GameState_AddKeeper(Keeper* keeper) {
  LinkedList_Add(gameState->keeperPool, keeper->name);
}
LinkedList* GameState_GetKeeperPool() {
  return gameState->keeperPool;
}

void GameState_AddBonus(Bonus* b) {
  LinkedList_Add(gameState->bonusPool, b->name);
}
LinkedList* GameState_GetBonusPool() {
  return gameState->bonusPool;
}
void GameState_ClearBonusPool() {
  LinkedList_Destroy(gameState->bonusPool);
}