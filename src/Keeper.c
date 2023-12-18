#include "Keeper.h"

Keeper* Keeper_Create(float x, float y) {
  Keeper* keeper = (Keeper*)malloc(sizeof(Keeper));
  Sprite* entity = Sprite_Create();
  Sprite_SetPosition(entity, x, y);
}

void Keeper_Destroy(Keeper* keeper) {
  if (keeper->entity) {
    Sprite_Destroy(keeper->entity);
  }
  free(keeper);
}

void simulatorCallBack(Keeper* keeper) {
  // if (keeper->state == "upacking") {
  //   if (keeper->actionLogicCount > 0) {
  //     keeper->actionLogicCount--; 
  //   } else {
  //     Keeper_Destroy(keeper);
  //   }
  // }
}