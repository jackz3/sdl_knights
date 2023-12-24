#include "EntityManager.h"
#include <stdio.h>
#include <stdlib.h>

EntityManager *EntityManager_GetInstance()
{
    static EntityManager *instance;
    if (instance == NULL)
    {
        instance = (EntityManager *)malloc(sizeof(EntityManager));
        if (instance != NULL)
        {
            instance->entities = NULL;
            instance->entityCount = 0;
        }
    }
    return instance;
}

bool EntityManager_CreateEntity(EntityManager *manager, const char *name, void *charactor)
{
    Sprite *newEntity = Sprite_Create();
    if (!newEntity)
    {
        return false;
    }

    EntityNode *newNode = malloc(sizeof(EntityNode));
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';
    newNode->entity = newEntity;
    newNode->charactor = charactor;
    newNode->next = manager->entities;

    manager->entities = newNode;
    manager->entityCount++;

    return true;
}

Sprite *EntityManager_GetEntity(EntityManager *manager, const char *name)
{
    EntityNode *node = manager->entities;
    while (node)
    {
        if (strcmp(node->name, name) == 0)
        {
            return node->entity;
        }

        node = node->next;
    }
    return NULL;
}
void* EntityManager_GetCharactor(EntityManager* manager, const char* name) {
    EntityNode *node = manager->entities;
    while (node)
    {
        if (strcmp(node->name, name) == 0)
        {
            return node->charactor;
        }
        node = node->next;
    }
    return NULL;
}

void EntityManager_RemoveEntity(EntityManager *manager, const char *name)
{
    EntityNode *prev = NULL;
    EntityNode *node = manager->entities;

    while (node)
    {
        if (strcmp(node->name, name) == 0)
        {
            if (prev)
            {
                prev->next = node->next;
            }
            else
            {
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

void EntityManager_UpdateAll(EntityManager *manager)
{
    EntityNode *node = manager->entities;
    while (node)
    {
        // GameEntity_Update(node->entity);
        node = node->next;
    }
}

void EntityManager_DeleteAll(EntityManager *manager)
{
    while (manager->entities)
    {
        EntityNode *node = manager->entities;
        manager->entities = node->next;
        Sprite_Destroy(node->entity);
        free(node);
    }

    manager->entityCount = 0;
}

void EntityManager_Simulate(EntityManager *manager)
{
    EntityNode *node = manager->entities;
    while (node)
    {
        EntityNode *nextNode = node->next;
        printf("simulator %s\n", node->name);
        Sprite_NextFrame(node->entity, &node->charactor);
        node = nextNode;
    }
}

int compSprites(const void *a, const void *b)
{
    return (*(Sprite **)a)->y - (*(Sprite **)b)->y;
}

void EntityManager_Render(EntityManager *manager)
{
    Sprite **sprites = (Sprite **)malloc(manager->entityCount * sizeof(Sprite *));
    EntityNode *node = manager->entities;
    int i = 0;
    while (node)
    {
        if (node->entity != NULL)
        {
            *(sprites + i++) = node->entity;
        }
        node = node->next;
    }
    qsort(sprites, i, sizeof(Sprite *), compSprites);

    for (int j = 0; j < i; j++)
    {
        Sprite *sprite = *(sprites + j);
        Sprite_Render(sprite);
    }
    free(sprites);
}

bool checkCollision(int ra[4], Sprite *s1, int rb[4], Sprite *s2, int rangeFix[2], int attackRange)
{
    int ax;
    int ay;
    int az;
    int aw;
    int ah;
    int bx;
    int by;
    int bz;
    int bw;
    int bh;

    aw = ra[2];
    ah = ra[3];
    ay = s1->y;
    az = ra[1] + s1->sy;
    if (!s1->toward)
    {
        ax = ra[0] + s1->x;
        if (rangeFix)
        {
            ax += rangeFix[0];
            aw += rangeFix[1];
        }
    }
    else
    {
        ax = -ra[0] + s1->x - aw;
        if (rangeFix)
        {
            ax += rangeFix[1] + rangeFix[0];
            aw += rangeFix[1];
        }
    }

    bw = rb[2];
    bh = rb[3];
    bz = rb[1] + s2->sy;
    by = s2->y;
    if (!s2->toward)
    {
        bx = rb[0] + s2->x;
    }
    else
    {
        bx = -rb[0] + s2->x - bw;
    }

    if (ax > bx - aw && ax < bx + bw)
    {
        if (az > bz - ah && az < bz + bh)
        {
            if (abs(ay - by) < attackRange)
            {
                return true;
            }
        }
    }
    return false;
    // return true;
}
bool collisionDetector(Sprite *s1, Sprite *s2, int attackRange, bool bodyMode, int *rangeFix)
{
    AttackRegion *attackRegion = s1->actions[s1->actionIndex].actionFrames[s1->frameIndex].r;
    int(*regionAttack)[4];
    int regionAttackLength = 0;
    if (bodyMode)
    {
        regionAttack = attackRegion->b;
        regionAttackLength = attackRegion->bCount;
    }
    else
    {
        regionAttack = attackRegion->a;
        regionAttackLength = attackRegion->aCount;
    }
    AttackRegion *bodyRegion = s2->actions[s2->actionIndex].actionFrames[s2->frameIndex].r;
    int (*regionBody)[4] = bodyRegion->b;
    int regionBodyLength = bodyRegion->bCount;
    int atRange = attackRange == 999 ? 9 : attackRange;
    for (int n = 0, m = regionAttackLength; n < m; n++)
    {
        int (*ra)[4] = &regionAttack[n];
        for (int i = 0, j = regionBodyLength; i < j; i++)
        {
            int (*rb)[4] = &regionBody[i];
            if (checkCollision(*ra, s1, *rb, s2, rangeFix, atRange))
            {
                return true;
            }
        }
    }
    return false;
}