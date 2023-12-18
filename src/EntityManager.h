#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <stdbool.h>
#include "Sprite.h"

typedef struct EntityNode {
    char name[64];
    Sprite* entity;
    void* charactor;
    struct EntityNode* next;
} EntityNode;

typedef struct {
    EntityNode* entities;
    size_t entityCount;
} EntityManager;

EntityManager* EntityManager_GetInstance();

bool EntityManager_CreateEntity(EntityManager* entityManager, const char* name, void* charactor);

Sprite* EntityManager_GetEntity(EntityManager* entityManager, const char* name);

void EntityManager_RemoveEntity(EntityManager* entityManager, const char* name);

void EntityManager_UpdateAll(EntityManager* entityManager);

void EntityManager_Render(EntityManager* entityManager);

void EntityManager_DeleteAll(EntityManager* entityManager);

void EntityManager_RenderSprite(EntityManager* EntityManager);
void EntityManager_Simulate(EntityManager* entityManager);

#endif
