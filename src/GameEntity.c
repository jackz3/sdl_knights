#include "GameEntity.h"
#include "config.h"

GameEntity *GameEntity_Create()
{
    GameEntity *entity = (GameEntity *)malloc(sizeof(GameEntity));
    if (entity != NULL)
    {
        // entity->rect = (SDL_Rect){0, 0, 0, 0};
        entity->m_texture = NULL;
        entity->m_colliders = NULL;
        entity->m_colliderCount = 0;
        entity->m_sprite = NULL;
    }
    return entity;
}

void GameEntity_Destroy(GameEntity *entity)
{
    if (entity != NULL)
    {
        if (entity->m_texture != NULL)
        {
            TexturedRectangle_Destroy(entity->m_texture);
            entity->m_texture = NULL;
        }

        if (entity->m_colliders != NULL)
        {
            for (size_t i = 0; i < entity->m_colliderCount; i++)
            {
                BoxCollider2D_Destroy(entity->m_colliders[i]);
            }
            free(entity->m_colliders);
            entity->m_colliders = NULL;
            entity->m_colliderCount = 0;
        }

        free(entity);
    }
}

void UpdateGameEntity(GameEntity *entity)
{
    // Update the position of our collider,
    // to be the same as the position of our Sprite component
    // if (entity->m_texture != NULL) {
    //    int x = GetPositionX(entity->m_texture);
    //    int y = GetPositionY(entity->m_texture);
    //    int w = GetWidth(entity->m_texture);
    //    int h = GetHeight(entity->m_texture);
    //}
}

void GameEntity_Render(GameEntity *entity)
{
    if (entity->m_texture != NULL)
    {
        TexturedRectangle_Render(entity->m_texture, entity->x, entity->y, entity->w, entity->h);
    }

    // for (size_t i = 0; i < entity->m_colliderCount; i++) {
    //     if (entity->m_colliders[i] != NULL) {
    //         SDL_SetRenderDrawColor(entity->m_renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
    //         SDL_RenderDrawRect(entity->m_renderer, entity->m_colliders[i] ->colliderRectangle);
    //     }
    // }
}

void GameEntity_AddTexturedRectangleComponent(GameEntity *entity, SDL_Renderer *renderer, const char *spritepath, SDL_Rect *srcRect)
{
    if (entity->m_texture != NULL)
    {
        TexturedRectangle_Destroy(entity->m_texture);
    }
    entity->m_texture = TexturedRectangle_Create(renderer, spritepath, srcRect);
}

void GameEntity_AddSprite(GameEntity *entity, Sprite *sprite)
{
    if (entity->m_sprite != NULL)
    {
        Sprite_Destroy(entity->m_sprite);
    }
    entity->m_sprite = sprite;
}
// void GameEntity_AddTexturedRectangleComponentWithColorKey(GameEntity* entity, const char* spritepath, int redcolorkey, int greencolorkey, int bluecolorkey) {
//     if (entity->m_texture != NULL) {
//         TexturedRectangle_Destroy(entity->m_texture);
//     }
//     entity->m_texture = TexturedRectangle_CreateWithColorKey(spritepath, redcolorkey, greencolorkey, bluecolorkey);
// }

void GameEntity_AddBoxCollider2D(GameEntity *entity)
{
    entity->m_colliderCount++;
    entity->m_colliders = (BoxCollider2D **)realloc(entity->m_colliders, sizeof(BoxCollider2D *) * entity->m_colliderCount);
    entity->m_colliders[entity->m_colliderCount - 1] = CreateBoxCollider2D();
}

TexturedRectangle *GameEntity_GetTexturedRectangle(GameEntity *entity)
{
    return entity->m_texture;
}

BoxCollider2D *GameEntity_GetBoxCollider2D(GameEntity *entity, size_t index)
{
    if (index < entity->m_colliderCount)
    {
        return entity->m_colliders[index];
    }
    return NULL;
}

void GameEntity_SetPosition(GameEntity *entity, float x, float y)
{
    entity->x = x;
    entity->y = y;

    for (size_t i = 0; i < entity->m_colliderCount; i++)
    {
        if (entity->m_colliders[i] != NULL)
        {
            BoxCollider2D_SetAbsolutePosition(entity->m_colliders[i], x, y);
        }
    }
}

void GameEntity_SetDimensions(GameEntity *entity, int w, int h)
{
    entity->w = w;
    entity->h = h;

    for (size_t i = 0; i < entity->m_colliderCount; i++)
    {
        if (entity->m_colliders[i] != NULL)
        {
            BoxCollider2D_SetDimensions(entity->m_colliders[i], w, h);
        }
    }
}

void GameEntity_RenderSprite(GameEntity *entity)
{
    Sprite *sprite = entity->m_sprite;
    // var region = sprite.config.actions[sprite.actionIndex].f[sprite.frameIndex].r;
    // 如果资源池里没有该精灵对应的资源，跳过渲染。
    // if (!resourcePool[sprite.resourceID]) continue;
    Action *action = sprite->actions + sprite->actionIndex;
    // 如果没有该精灵当前对应的动作，跳过渲染。
    if (action == NULL)
        return;
    ActionFrame *actionFrame = action->actionFrames + sprite->frameIndex;
    // 如果没有该精灵当前对应的动作帧，跳过渲染。
    if (actionFrame == NULL)
        return;
    Frame *frame = actionFrame->frame;
    // 如果没有该精灵当前对应的帧，跳过渲染。
    if (frame == NULL)
        return;

    if (sprite->blink)
    {
        sprite->blinkState = !sprite->blinkState;
    }
    if (!sprite->blink || sprite->blinkState)
    {
        TexturedRectangle_SetSrcPosition(entity->m_texture, frame->left, frame->top);
        TexturedRectangle_SetSrcDimension(entity->m_texture, frame->width, frame->height);
        printf("rendering text\n");
        TexturedRectangle_Render(entity->m_texture,
                                 (entity->x + sprite->sx + actionFrame->offsetX - 0) * SCALE,
                                 (entity->y + sprite->sy + actionFrame->offsetY - 0) * SCALE,
                                 frame->width * SCALE, frame->height * SCALE);
        //  sprite->toward ? !actionFrame->flip : actionFrame->flip,
        //  actionFrame->offsetX * SCALE,
        //  actionFrame->offsetY * SCALE);
    }
}