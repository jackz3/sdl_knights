#include "EntityManager.h"
#include <stdio.h>
#include <stdlib.h>

EntityManager* EntityManager_GetInstance() {
    static EntityManager* instance;
    if (instance == NULL) {
        instance = (EntityManager*)malloc(sizeof(EntityManager));
        if (instance != NULL) {
            instance->entities = NULL;
            instance->entityCount = 0;
        }
    }
    return instance;
}

bool EntityManager_CreateEntity(EntityManager* manager, const char* name, void* charactor) {
    Sprite* newEntity = Sprite_Create();
    if (!newEntity) {
        return false;
    }

    EntityNode* newNode = malloc(sizeof(EntityNode));
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';
    newNode->entity = newEntity;
    newNode->charactor = charactor;
    newNode->next = manager->entities;

    manager->entities = newNode;
    manager->entityCount++;

    return true;
}

Sprite* EntityManager_GetEntity(EntityManager* manager, const char* name) {
    EntityNode* node = manager->entities;
    while (node) {
        if (strcmp(node->name, name) == 0) {
            return node->entity;
        }

        node = node->next;
    }

    return NULL;
}

void EntityManager_RemoveEntity(EntityManager* manager, const char* name) {
    EntityNode* prev = NULL;
    EntityNode* node = manager->entities;

    while (node) {
        if (strcmp(node->name, name) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                manager->entities = node->next;
            }

            Sprite_Destroy(node->entity);
            free(node);
            manager->entityCount--;
            return;
        }

        prev = node;
        node = node->next;
    }
}

void EntityManager_UpdateAll(EntityManager* manager) {
    EntityNode* node = manager->entities;
    while (node) {
        // GameEntity_Update(node->entity);
        node = node->next;
    }
}

// void EntityManager_Render(EntityManager* manager) {
//     EntityNode* node = manager->entities;
//     while (node) {
//         Sprite_Render(node->entity);
//         node = node->next;
//     }
// }

void EntityManager_DeleteAll(EntityManager* manager) {
    while (manager->entities) {
        EntityNode* node = manager->entities;
        manager->entities = node->next;
        Sprite_Destroy(node->entity);
        free(node);
    }

    manager->entityCount = 0;
}

void EntityManager_Simulate(EntityManager* manager) {
    EntityNode* node = manager->entities;
    while (node) {
        EntityNode* nextNode = node->next;
        Sprite_NextFrame(node->entity, &node->charactor);
        node = nextNode;
    }
}

int compSprites (const void* a, const void* b) {
   return (*(Sprite**)a)->y - (*(Sprite**)b)->y;
}

void EntityManager_Render(EntityManager* manager) {
    Sprite** sprites = (Sprite**)malloc(manager->entityCount * sizeof(Sprite*));
    EntityNode* node = manager->entities;
    int i = 0;
    while (node) {
        if (node->entity != NULL) {
            *(sprites + i++) = node->entity; 
        }
        node = node->next;
    }
    qsort(sprites, i, sizeof(Sprite*), compSprites);
    
    for(int j=0; j < i; j++) {
        Sprite* sprite = *(sprites + j);
        Sprite_Render(sprite); 
    }
    free(sprites);
}