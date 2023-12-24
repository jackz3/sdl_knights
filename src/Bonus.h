#ifndef Bonus_h
#define Bonus_h
#include "Sprite.h"

typedef struct 
{
	int aaa;
} BonusValue;

enum BonusState {
  Bonus_Discover,
  Bonus_Unpacking,
	Bonus_GetBy,
	Bonus_Stand,
};

typedef struct {
  char name[16];
	char actionName[32];
	int actionLogicCount;
  enum BonusState state;
	Sprite* sprite;
	// var bonusValueMap = {
	// 	'silverbag': 140,
	// 	'silverchest': 400,
	// 	'goldbag': 180,
	// 	'goldchest': 600,
	// 	'jewelrybag': 240,
	// 	'jewelrychest': 800,
	// 	'fruit': 320,
	// 	'fruit-s1': 80,
	// 	'fruit-s2': 100,
	// 	'bread': 160,
	// 	'bread-s': 80,
	// 	'salad': 320,
	// 	'salad-s': 100,
	// 	'chicken': 560,
	// 	'chicken-s': 160,
	// 	'ham': 120,
	// 	'ham-s': 40
	// };
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

#endif