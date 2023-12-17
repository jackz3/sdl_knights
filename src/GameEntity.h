#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <stdlib.h>
#include <string.h>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>
#include "TexturedRectangle.h"
#include "Collider.h"
#include "Sprite.h"

typedef struct {
    // char name[64];
    // Components
    float x;
    float y;
    int w;
    int h;
    TexturedRectangle* m_texture;
    BoxCollider2D** m_colliders;
    Sprite* m_sprite;
    size_t m_colliderCount;
} GameEntity;

// Constructors
GameEntity* GameEntity_Create();
// GameEntity* CreateGameEntityWithRenderer(SDL_Renderer* renderer);

// Destructor
void GameEntity_Destroy(GameEntity* entity);

// Update (called every loop)
void UpdateGameEntity(GameEntity* entity);

// Render our Game Entity (In the render portion)
void GameEntity_Render(GameEntity* entity);
// void GameEntity_Render2(GameEntity* entity, int x, int y, int w, int h);

// Adding Rectangle Components
void GameEntity_AddTexturedRectangleComponent(GameEntity* entity, SDL_Renderer* renderer, const char* spritepath, SDL_Rect* srcRect);
void GameEntity_AddTexturedRectangleComponentWithColorKey(GameEntity* entity, const char* spritepath, int redcolorkey, int greencolorkey, int bluecolorkey);

// Add another Box Collider to our object
void GameEntity_AddBoxCollider2D(GameEntity* entity);

// Retrieve Components
TexturedRectangle* GameEntity_GetTexturedRectangle(GameEntity* entity);
BoxCollider2D* GameEntity_GetBoxCollider2D(GameEntity* entity, size_t index);

void GameEntity_SetPosition(GameEntity* entity, float x, float y);
void GameEntity_SetDimensions(GameEntity* entity, int w, int h);

void GameEntity_AddSprite(GameEntity* entity, Sprite* sprite);
void GameEntity_RenderSprite(GameEntity* entity);


#endif