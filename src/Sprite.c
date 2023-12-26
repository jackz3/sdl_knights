#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "Sprite.h"
#include "cJSON.h"
#include "util.h"
#include "sdl_app.h"

static int SCALE = 1;
Sprite *Sprite_Create()
{
  Sprite *sprite = (Sprite *)malloc(sizeof(Sprite));
  if (sprite != NULL)
  {
    sprite->m_texture = NULL;
    sprite->resourceID = 0;
    sprite->frames = NULL;
    sprite->framesLen = 0;
    sprite->actions = NULL;
    sprite->x = 0;
    sprite->y = 0;
    sprite->ax = 0;
    sprite->ay = 0;
    sprite->vx = 0;
    sprite->vy = 0;
    sprite->sx = 0;
    sprite->sy = 0;
    sprite->toward = 0;
    sprite->actionIndex = 0;
    sprite->loop = false;
    sprite->blink = false;
    sprite->blinkState = false;
    sprite->display = false;
    sprite->frameIndex = 0;
    sprite->frameCount = 0;
    sprite->flash = false;
    sprite->flashState = false;
    sprite->autoNextFrame = true;
    sprite->simulatorCallBack = NULL;
    sprite->actionCallBack = NULL;
    sprite->onEnd = NULL;
  }
  return sprite;
}

int Sprite_GetActionId(Sprite* sprite, const char* actionName) {
		Action* actions = sprite->actions;
		int ret = 0;
		for (int n = 0, m = sprite->actionsLen; n < m; n++){
      char* lowerName = toLowerCase(actions[n].name);
			if (strcmp(lowerName, actionName) == 0) {
				ret = n;
        free(lowerName);
        break;
			}
      free(lowerName);
		}
		return ret;
}

void formatFrames(Sprite *sprite, cJSON *json)
{
  cJSON *jsonFrames = NULL;
  cJSON *jsonFrame = NULL;
  jsonFrames = cJSON_GetObjectItemCaseSensitive(json, "frames");
  int frameLength = cJSON_GetArraySize(jsonFrames);
  if (sprite->frames != NULL)
  {
    free(sprite->frames);
  }
  sprite->frames = (Frame *)malloc(sizeof(Frame) * frameLength);
  sprite->framesLen = frameLength;
  int j = 0;
  cJSON_ArrayForEach(jsonFrame, jsonFrames)
  {
    cJSON *c = cJSON_GetObjectItemCaseSensitive(jsonFrame, "c");
    cJSON *i = cJSON_GetObjectItemCaseSensitive(jsonFrame, "i");
    cJSON *d = cJSON_GetObjectItemCaseSensitive(jsonFrame, "d");
    cJSON *n = cJSON_GetObjectItemCaseSensitive(jsonFrame, "n");

    Frame *frame = sprite->frames + j;
    // frame = (Frame *)malloc(sizeof(Frame));
    strncpy(frame->id, d->valuestring, sizeof(frame->id));
    int len = 0;
    char **split = string_split(c->valuestring, "_", &len);
    if (len == 4)
    {
      frame->left = atof(*split);
      frame->top = atof(*(split + 1));
      frame->width = atoi(*(split + 2));
      frame->height = atoi(*(split + 3));
      // printf("frame %s, %f,%f,%i,%i\n", frame->id, frame->left, frame->top, frame->width, frame->height);
    }
    else
    {
      printf("parse frames error\n");
    }
    for (int x = 0; x < len; x++)
    {
      free(split[x]);
    }
    free(split);
    j++;
  }
}

Frame *getFrameById(Frame *frames, int framesLen, const char *id)
{
  for (int n = 0, m = framesLen; n < m; n++)
  {
    if (strcmp(frames[n].id, id) == 0)
    {
      return frames + n;
    }
  }
  return NULL;
}

int (*parseAttackRegion(cJSON *r, ActionFrame *actionFrames, int j, const char* keyName, int* count))[4]
{
  cJSON *bJson = cJSON_GetObjectItemCaseSensitive(r, keyName);
  if (bJson == NULL)
  {
    // (actionFrames + j)->r->b = NULL;
    // (actionFrames + j)->r->bCount = 0;
    return NULL;
    *count = 0;
  }
  else
  {
    cJSON *bItemJson = NULL;
    int bCount = cJSON_GetArraySize(bJson);
    *count = bCount;
    if (bCount == 0) {
      return NULL;
    }
    (actionFrames + j)->r->bCount = bCount;
    int(*b)[4] = (int(*)[4])malloc(sizeof(int(*)[4]) * bCount);
    int x = 0;
    cJSON_ArrayForEach(bItemJson, bJson)
    {
      if (bItemJson == NULL)
      {
        b = NULL;
      }
      else
      {
        int len = cJSON_GetArraySize(bItemJson);
        if (len != 4)
        {
          printf("attack region is not 4\n");
        }
        else
        {
          for (int k = 0; k < len; k++)
          {
            b[x][k] = cJSON_GetArrayItem(bItemJson, k)->valueint;
          }
        }
      }
      x++;
    }
    // (actionFrames + j)->r->b = b;
    return b;
  }
}
void formatActions(Sprite *sprite, cJSON *json)
{
  cJSON *jsonActions = NULL;
  cJSON *jsonAction = NULL;
  jsonActions = cJSON_GetObjectItemCaseSensitive(json, "actions");
  int actionLength = cJSON_GetArraySize(jsonActions);
  if (sprite->actions != NULL)
  {
    free(sprite->actions);
  }
  sprite->actions = (Action *)malloc(sizeof(Action) * actionLength);
  sprite->actionsLen = actionLength;
  int i = 0;
  cJSON_ArrayForEach(jsonAction, jsonActions)
  {
    cJSON *n = cJSON_GetObjectItemCaseSensitive(jsonAction, "n");
    cJSON *v = cJSON_GetObjectItemCaseSensitive(jsonAction, "v");
    cJSON *framesJson = cJSON_GetObjectItemCaseSensitive(jsonAction, "f");

    Action *action = sprite->actions + i;
    strncpy(action->name, n->valuestring, sizeof(action->name));
    strncpy(action->value, v->valuestring, sizeof(action->value));

    // cJSON *actionFramesJson = NULL;
    cJSON *actionFrameJson = NULL;
    int actionFramesLength = cJSON_GetArraySize(framesJson);
    ActionFrame *actionFrames = (ActionFrame *)malloc(sizeof(ActionFrame) * actionFramesLength);
    action->actionFrames = actionFrames;
    action->framesLen = actionFramesLength;
    int j = 0;
    cJSON_ArrayForEach(actionFrameJson, framesJson)
    {
      cJSON *flip = cJSON_GetObjectItemCaseSensitive(actionFrameJson, "l");
      cJSON *duration = cJSON_GetObjectItemCaseSensitive(actionFrameJson, "u");
      cJSON *offsetX = cJSON_GetObjectItemCaseSensitive(actionFrameJson, "x");
      cJSON *offsetY = cJSON_GetObjectItemCaseSensitive(actionFrameJson, "y");
      cJSON *f = cJSON_GetObjectItemCaseSensitive(actionFrameJson, "f");
      // cJSON *d = cJSON_GetObjectItemCaseSensitive(actionFrameJson, "d");
      cJSON *r = cJSON_GetObjectItemCaseSensitive(actionFrameJson, "r");
      int flp = atoi(flip->valuestring);
      int du = atoi(duration->valuestring);
      float ox = atof(offsetX->valuestring);
      float oy = atof(offsetY->valuestring);
      Frame *frame = getFrameById(sprite->frames, sprite->framesLen, f->valuestring);
      if (frame == NULL)
      {
        printf("frame null\n");
      }
      (actionFrames + j)->flip = flp;
      (actionFrames + j)->duration = du;
      (actionFrames + j)->offsetX = ox;
      (actionFrames + j)->offsetY = oy;
      (actionFrames + j)->frame = frame;
      // printf("action frame: %i %i %f %f %s \n", flp, du, ox, oy, frame->id);
      if (r == NULL) {
        (actionFrames + j)->r = NULL;
      } else {
        (actionFrames + j)->r = (AttackRegion*)malloc(sizeof(AttackRegion));
        int count = 0;
        (actionFrames + j)->r->b = parseAttackRegion(r, actionFrames, j, "b", &count);
        (actionFrames + j)->r->bCount = count;
        (actionFrames + j)->r->a = parseAttackRegion(r, actionFrames, j, "a", &count);
        (actionFrames + j)->r->aCount = count;
      }
      j++;
    }
    i++;
  }
}


void Sprite_init(Sprite *sprite, const char *fileName)
{
  struct stat filestatus;
  int file_size;
  char *file_contents;
  FILE *fp;
  if (stat(fileName, &filestatus) != 0)
  {
    fprintf(stderr, "File %s not found\n", fileName);
    exit(1);
  }
  file_size = filestatus.st_size;
  file_contents = (char *)malloc(filestatus.st_size);
  if (file_contents == NULL)
  {
    fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
    exit(1);
  }

  fp = fopen(fileName, "rt");
  if (fp == NULL)
  {
    fprintf(stderr, "Unable to open %s\n", fileName);
    //fclose(fp);
    free(file_contents);
    exit(1);
  }
  fread(file_contents, file_size, 1, fp);
  fclose(fp);

  cJSON *json = cJSON_Parse(file_contents);
  if (json == NULL)
  {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL)
    {
      fprintf(stderr, "Error before: %s\n", error_ptr);
    }
    free(file_contents);
    cJSON_Delete(json);
    exit(1);
  }

  formatFrames(sprite, json);
  formatActions(sprite, json);

  cJSON_Delete(json);
  free(file_contents);
}

void Sprite_Destroy(Sprite *sprite)
{
  if (sprite != NULL)
  {
    if (sprite->m_texture != NULL)
    {
      TexturedRectangle_Destroy(sprite->m_texture);
      sprite->m_texture = NULL;
    }
    if (sprite->frames != NULL)
    {
      free(sprite->frames);
      sprite->frames = NULL;
    }
    if (sprite->actions != NULL)
    {
      free(sprite->actions);
      sprite->actions = NULL;
    }
    free(sprite);
  }
}

void Sprite_Render(Sprite* sprite) {
  //if (sprite->actionsLen > 20) {
  //  printf("sprite rendering %i\n", sprite->actionsLen);
  //}
  if (sprite->m_texture != NULL) {
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
        TexturedRectangle_SetSrcPosition(sprite->m_texture, frame->left, frame->top);
        TexturedRectangle_SetSrcDimension(sprite->m_texture, frame->width, frame->height);
        bool flip = sprite->toward ? !actionFrame->flip : actionFrame->flip;
        float tx = (sprite->x + sprite->sx + actionFrame->offsetX - Camera_GetX());
        if (!flip) {
        TexturedRectangle_Render(sprite->m_texture,
                                 tx * SCALE,
                                 (sprite->y + sprite->sy + actionFrame->offsetY - Camera_GetY()) * SCALE,
                                 frame->width * SCALE, frame->height * SCALE);
        } else {
        TexturedRectangle_RenderEx(sprite->m_texture,
                                 (tx)  * SCALE,
                                 (sprite->y + sprite->sy + actionFrame->offsetY - Camera_GetY()) * SCALE,
                                 frame->width * SCALE, frame->height * SCALE, SDL_FLIP_HORIZONTAL);

        }
        //  actionFrame->offsetX * SCALE,
        //  actionFrame->offsetY * SCALE);
    }
    else {
			TexturedRectangle_Render(sprite->m_texture, sprite->x, sprite->y, sprite->w, sprite->h);
    }
  }
}

void Sprite_SetPosition(Sprite* sprite, float x, float y) {
  sprite->x = x;
  sprite->y = y;
}
void Sprite_SetDimensions(Sprite* sprite, int w, int h) {
  sprite->w = w;
  sprite->h = h;
}

TexturedRectangle* Sprite_GetTexturedRectangle(Sprite* sprite) {
  return sprite->m_texture;
}

void Sprite_AddTexturedRectangle(Sprite* sprite, SDL_Renderer* renderer, const char* spritepath, SDL_Rect* srcRect) {
  if (sprite->m_texture != NULL)
  {
      TexturedRectangle_Destroy(sprite->m_texture);
  }
  sprite->m_texture = TexturedRectangle_Create(renderer, spritepath, srcRect);
}

void Sprite_NextFrame(Sprite *sprite, void **charactor)
{
  sprite->frameCount++;
  if (sprite->actions + sprite->actionIndex == NULL)
    return;

  if (sprite->simulatorCallBack != NULL)
  {
    sprite->simulatorCallBack(charactor);
    if (*charactor == NULL) {
      return;
    }
  }
  sprite->ax && (sprite->vx += sprite->ax);
  sprite->ay && (sprite->vy += sprite->ay);
  sprite->vx && (sprite->x += sprite->vx);
  sprite->vy && (sprite->y += sprite->vy);
  //printf("frame id: %s, index:%i, frameIndex: %i, count: %i\n",sprite->actions[sprite->actionIndex].name, sprite->actionIndex, sprite->frameIndex, sprite->frameCount);
  //if (sprite->frameIndex == 11 && sprite->frameCount == 3 && sprite->actionIndex == 1) {
  //  printf("stop\n");
  //}
  ActionFrame *actionFrame = sprite->actions[sprite->actionIndex].actionFrames + sprite->frameIndex;
  if (actionFrame == NULL)
  {
    sprite->frameIndex = 0;
    actionFrame = sprite->actions[sprite->actionIndex].actionFrames + sprite->frameIndex;
  }
  if (sprite->frameCount > actionFrame->duration - 1)
  {
    sprite->frameCount = 0;
    Sprite_nextActionFrame(sprite, charactor);
  }
}

void Sprite_nextActionFrame(Sprite *sprite, void *charactor)
{
  if (!sprite->autoNextFrame)
    return;
  sprite->frameIndex++;
  if (sprite->frameIndex > sprite->actions[sprite->actionIndex].framesLen - 1)
  {
    if (sprite->loop)
    {
      sprite->frameIndex = 0;
      // onLoop && onLoop();
    }
    else
    {
      sprite->frameIndex--;
      if (sprite->onEnd != NULL) {
        sprite->onEnd(charactor);
      }
    }
  }
}

void Sprite_SetSimulatorCallBack(Sprite *sprite, void (*func)(void **))
{
  sprite->simulatorCallBack = func;
}
void Sprite_simulatorCallBack(Sprite *sprite, void **charactor)
{
  if (sprite->simulatorCallBack != NULL)
  {
    sprite->simulatorCallBack(charactor);
  }
}

void Sprite_SetActionCallBack(Sprite *sprite, void (*func)(void *charactor, const char *actionName, const char* actionParam))
{
  sprite->actionCallBack = func;
}
void Sprite_DoAction(Sprite *sprite, void *charactor, const char *actionName, const char* actionParam)
{
  if (sprite->actionCallBack != NULL)
  {
    sprite->actionCallBack(charactor, actionName, actionParam);
  }
}

void Sprite_SetOnEnd(Sprite* sprite, void (*func)(void** charactor)) {
  sprite->onEnd = func;
}