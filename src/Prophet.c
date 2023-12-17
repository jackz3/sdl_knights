#include <stdlib.h>
#include <string.h>
#include "Prophet.h"
#include "sdl_app.h"
#include "EntityManager.h"
#include "Collider.h"


extern SDLApp* app;

void Prophet_ActionCallback(void* charactor, const char* actionName) {
  Prophet* prophet = (Prophet*)charactor;
  if (strcmp(actionName, "prophet") == 0) {
    // do something
    // sprite->    
    prophet->state = Prophet_prophet;
			// sprite.actionIndex = actionEnum['prophet'];
    prophet->entity->m_sprite->actionIndex = 0;
    prophet->entity->m_sprite->frameIndex = 0;
    prophet->entity->m_sprite->loop = false;
			// sprite.onEnd = function(){
			// 	destory();
			// };
  }
}

void Prophet_Simulator(void* charactor) {
  Prophet* prophet = (Prophet*)charactor;
  if (prophet->state == Prophet_Stand){
				// doAction('prophet');
      Sprite_DoAction(prophet->entity->m_sprite, charactor, "prophet");
  } else if (prophet->state == Prophet_prophet){
    if (prophet->entity->m_sprite->frameIndex == 11 && prophet->entity->m_sprite->frameCount == 5){
					// new Effect({
					// 	spriteID: 'effect1',
					// 	x: sprite.x,
					// 	y: sprite.y,
					// 	toward: sprite.toward,
					// 	actionName: 'smoke',
					// 	life: 36
					// });
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
      prophet->entity->m_sprite->sy = prophet->z;
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
    prophet->entity->m_sprite->sy = prophet->z;
  }
}

Prophet* Prophet_Create(float x, float y) {
  Prophet* prophet = (Prophet*)malloc(sizeof(Prophet));
  strcpy(prophet->name, "prophet");
  strcpy(prophet->actionName, "stand");
  prophet->dx = 0;
  prophet->dy = 0;
  prophet->g = 0.292; 

  EntityManager_CreateEntity(EntityManager_GetInstance(), prophet->name);
  GameEntity* entity = EntityManager_GetEntityRef(EntityManager_GetInstance(), prophet->name);
  SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  GameEntity_AddTexturedRectangleComponent(entity, app->renderer, "./assets/images/prophet.png", rect);
  GameEntity_SetPosition(entity, x, y);
  // GameEntity_SetDimensions(entity, w, h);
  Sprite* sprite = Sprite_Create();
  GameEntity_AddSprite(entity, sprite);
  Sprite_init(sprite, "./assets/prophet.json");
  Sprite_SetActionCallBack(sprite, Prophet_ActionCallback);
  Sprite_SetSimulatorCallBack(sprite, Prophet_Simulator);
  prophet->entity = entity;
  printf("create prophet\n"); 
  return prophet;
}

void Prophet_Destroy(Prophet* prophet) {
  free(prophet);
}


void Prophet_render(Prophet* prophet) {
  GameEntity* entity = EntityManager_GetEntityRef(EntityManager_GetInstance(), prophet->name);
  GameEntity_Render(entity);
}
