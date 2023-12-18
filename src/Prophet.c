#include <stdlib.h>
#include <string.h>
#include "Prophet.h"
#include "sdl_app.h"
#include "EntityManager.h"
#include "Effect.h"


extern SDLApp* app;

static void onEnd(void* charactor) {
  Prophet* prophet = (Prophet*)charactor;
  EntityManager_RemoveEntity(EntityManager_GetInstance(), prophet->name);
  Prophet_Destroy(prophet); 
} 
void Prophet_ActionCallback(void* charactor, const char* actionName) {
  Prophet* prophet = (Prophet*)charactor;
  if (strcmp(actionName, "prophet") == 0) {
    // do something
    // sprite->    
    prophet->state = Prophet_prophet;
			// sprite.actionIndex = actionEnum['prophet'];
    prophet->sprite->actionIndex = 0;
    prophet->sprite->frameIndex = 0;
    prophet->sprite->loop = false;
    Sprite_SetOnEnd(prophet->sprite, onEnd);
  }
}

void Prophet_Simulator(void* charactor) {
  Prophet* prophet = (Prophet*)charactor;
  if (prophet->state == Prophet_Stand){
				// doAction('prophet');
      Sprite_DoAction(prophet->sprite, charactor, "prophet");
  } else if (prophet->state == Prophet_prophet){
    if (prophet->sprite->frameIndex == 11 && prophet->sprite->frameCount == 5){
      printf("creating effect index: %i\n", prophet->sprite->frameIndex);
      Effect* effect = Effect_Create("effect1", prophet->sprite->x, prophet->sprite->y, prophet->sprite->toward, "smoke", 36);
					// soundManager.play('smoke');
    } 
    if (prophet->z != 0 || prophet->vz != 0){
      prophet->vz += prophet->g;
      prophet->z += prophet->vz;
    }
    if (prophet->z > 0){
      prophet->z = 0;
      prophet->vz = -prophet->vz * 0.4;
      if (abs(prophet->vz) < 0.1){
        prophet->vz = 0;
      }
      prophet->sprite->sy = prophet->z;
						// new Effect({
						// 	spriteID: 'effect1',
						// 	x: sprite.x + Math.random() * 40 - 20,
						// 	y: sprite.y,
						// 	vx: Math.random() * 2 - 1,
						// 	vy: (Math.random() * 2 - 1) / 2.5,
						// 	toward: sprite.toward,
						// 	actionName: 'dust',
						// 	loop: true,
						// 	life: 15
						// });
    }
    prophet->sprite->sy = prophet->z;
  }
}

Prophet* Prophet_Create(float x, float y) {
  Prophet* prophet = (Prophet*)malloc(sizeof(Prophet));
  strcpy(prophet->name, "prophet");
  strcpy(prophet->actionName, "stand");
  prophet->dx = 0;
  prophet->dy = 0;
  prophet->vz = 0;
  prophet->z = 0;
  prophet->g = 0.292; 
  prophet->state = Prophet_Stand;

  EntityManager_CreateEntity(EntityManager_GetInstance(), prophet->name, prophet);
  Sprite* entity = EntityManager_GetEntity(EntityManager_GetInstance(), prophet->name);
  SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  Sprite_AddTexturedRectangle(entity, app->renderer, "./assets/images/prophet.png", rect);
  Sprite_SetPosition(entity, x, y);
  // GameEntity_SetDimensions(entity, w, h);
  Sprite_init(entity, "./assets/prophet.json");
  Sprite_SetActionCallBack(entity, Prophet_ActionCallback);
  Sprite_SetSimulatorCallBack(entity, Prophet_Simulator);
  prophet->sprite = entity;
  printf("create prophet\n"); 
  return prophet;
}

void Prophet_Destroy(Prophet* prophet) {
  if (prophet != NULL) {
    free(prophet);
    printf("destroy prophet\n");
  }
}


void Prophet_render(Prophet* prophet) {
  Sprite* sprite = EntityManager_GetEntity(EntityManager_GetInstance(), prophet->name);
  Sprite_Render(sprite);
}
