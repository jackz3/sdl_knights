#include "GameState.h"

static GameState* gameState;

void GameState_Init() {
  gameState = (GameState*)malloc(sizeof(GameState));
  gameState->keeperPool = LinkedList_Create();
  gameState->bonusPool = LinkedList_Create();
  gameState->textPool = LinkedList_Create();
  gameState->lancelotHealth = 80;
  gameState->lancelotPoint = 0;
  gameState->lancelotLife = 2;
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
LinkedList* GameState_GetTextPool() {
  return gameState->textPool;
}
void GameState_AddText(Text* text) {
  LinkedList_Add(gameState->textPool, text);
}
void GameState_ClearTextPool() {
  LinkedList_Destroy(gameState->textPool);
}

int GameState_GetLancelotPoint(){
			return gameState->lancelotPoint;
		}
int GameState_GetLancelotLife() {
			return gameState->lancelotLife;
		}
    void GameState_SetLancelotPoint (int value){
			gameState->lancelotPoint = value;
		}
	void GameState_SetLancelotLife (int value){
		 gameState->lancelotLife = value;
		}