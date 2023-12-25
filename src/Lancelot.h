#ifndef Lancelot_H
#define Lancelot_H

#include "Sprite.h"
#include "sdl_app.h"

enum LancelotState
{
  Lancelot_Stand,
  Lancelot_Jump,
  Lancelot_Jumpslash,
  Lancelot_Kick,
  Lancelot_Kickhit,
  Lancelot_Retreatslash,
  Lancelot_Wound3,
  Lancelot_Wound4,
  Lancelot_Die,
  Lancelot_Walkdefense,
  Lancelot_Heavyslash,
  Lancelot_Defenseshock,
  Lancelot_Wound1,
  Lancelot_Tired,
  Lancelot_Walk,
  Lancelot_Lightslash,
  Lancelot_Comboslash,
  Lancelot_Comboslash2,
  Lancelot_Comboslash3,
  Lancelot_Comboslash4,
  Lancelot_Comboslash5,
  Lancelot_Defense,
  Lancelot_Backslash,
  Lancelot_Powerslash,
  Lancelot_Revert,
};

enum ControlState {
  Computer,
  Player
};

typedef struct Lancelot
{
  char name[16];
	char actionName[32];
  float healthMax;
  float health;
  enum LancelotState state;
  float speed;
  float z;
  float vz;
  float g;
  enum ControlState controllState;
  int controllCount;
  int actionLogicCount;
  int actionID;
  int beHitCount;
  int flashLife;
  int comboFlag;
  int attackPower;
  int fallCount;
  bool victory;
  int victoryMask;
  int lastHealth;
  bool feedbackDamage;
  int multiple;
  Sprite* sprite;
} Lancelot;

Lancelot* Lancelot_Create(float x, float y, float health);
void Lancelot_Destroy(Lancelot* lancelot);

void Lancelot_Controller(Lancelot* lancelot, KeyState* keyState);

#endif