#include "GameState.h"

static GameState* gameState;

void GameState_Init() {
  gameState = (GameState*)malloc(sizeof(GameState));
  gameState->keeperPool = LinkedList_Create();
}
void GameState_Destroy(GameState* gameState) {
  free(gameState);
}

void GameState_AddKeeper(Keeper* keeper) {
  LinkedList_Add(gameState->keeperPool, keeper);
}
LinkedList* GameState_GetKeeperPool() {
  return gameState->keeperPool;
}
