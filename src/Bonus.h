#ifndef Bonus_h
#define Bonus_h
#include "Sprite.h"

enum BonusState {
  Bonus_Discover,
  Bonus_Unpacking,
	Bonus_Getby,
	Bonus_Stand,
};


typedef struct {
  char name[16];
	char actionName[32];
	int actionLogicCount;
  enum BonusState state;
	Sprite* sprite;
	// var bonusRecoverMap = {
	// 	'fruit': 32,
	// 	'fruit-s1': 8,
	// 	'fruit-s2': 10,
	// 	'bread': 16,
	// 	'bread-s': 10,
	// 	'salad': 32,
	// 	'salad-s': 10,
	// 	'chicken': 56,
	// 	'chicken-s': 16,
	// 	'ham': 12,
	// 	'ham-s': 4
	// };
} Bonus;

Bonus* Bonus_Create(const char* name, float x, float y, const char* actionName);
void Bonus_Destroy(Bonus* bonus);

void Bonus_GetBy(Bonus* bonus, void* charactor);
void Bonus_Unpack(Bonus* bonus);

#endif