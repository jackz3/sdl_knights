#include "Keeper.h"

Keeper* Keeper_Create(float x, float y) {
  Keeper* keeper = (Keeper*)malloc(sizeof(Keeper));
  GameEntity* entity = GameEntity_Create();
  GameEntity_SetPosition(entity, x, y);

}

void Keeper_Destroy(Keeper* keeper) {
  if (keeper->entity) {
    GameEntity_Destroy(keeper->entity);
  }
  free(keeper);
}

void simulatorCallBack(Keeper* keeper) {
  if (keeper->state == "upacking") {
    if (keeper->actionLogicCount > 0) {
      keeper->actionLogicCount--; 
    } else {
      Keeper_Destroy(keeper);
    }
  }
}