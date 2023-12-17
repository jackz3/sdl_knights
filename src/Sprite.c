#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "Sprite.h"
#include "cJSON.h"
#include "util.h"
#include "config.h"

Sprite *Sprite_Create()
{
  Sprite *sprite = (Sprite *)malloc(sizeof(Sprite));
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
  return sprite;
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
        printf("frame %s, %f,%f,%i,%i\n", frame->id, frame->left,frame->top,frame->width,frame->height);
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

        int flp = atoi(flip->valuestring);
        int du = atoi(duration->valuestring);
        float ox = atof(offsetX->valuestring);
        float oy = atof(offsetY->valuestring);
        Frame* frame = getFrameById(sprite->frames, sprite->framesLen, f->valuestring);
        if (frame == NULL) {
          printf("frame null\n");
        }
          (actionFrames + j)->flip = flp;
          (actionFrames + j)->duration = du;
          (actionFrames + j)->offsetX = ox;
          (actionFrames + j)->offsetY = oy;
          (actionFrames + j)->frame = frame;
          printf("action frame: %i %i %f %f %s \n", flp, du, ox, oy, frame->id);
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
    fclose(fp);
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
  if (sprite->frames != NULL)
  {
    free(sprite->frames);
  }
  if (sprite->actions != NULL)
  {
    free(sprite->actions);
  }
  free(sprite);
}

void Sprite_NextFrame(Sprite *sprite, void* charactor)
{
  sprite->frameCount++;
  if (sprite->actions + sprite->actionIndex == NULL)
    return;

  if (sprite->simulatorCallBack != NULL)
  {
    sprite->simulatorCallBack(charactor);
  }
  sprite->ax && (sprite->vx += sprite->ax);
  sprite->ay && (sprite->vy += sprite->ay);
  sprite->vx && (sprite->x += sprite->vx);
  sprite->vy && (sprite->y += sprite->vy);
  ActionFrame *actionFrame = sprite->actions[sprite->actionIndex].actionFrames + sprite->frameIndex;
  if (actionFrame == NULL)
  {
    sprite->frameIndex = 0;
    actionFrame = sprite->actions[sprite->actionIndex].actionFrames + sprite->frameIndex;
  }
  if (sprite->frameCount > actionFrame->duration - 1)
  {
    sprite->frameCount = 0;
    Sprite_nextActionFrame(sprite);
  }
}

void Sprite_nextActionFrame(Sprite *sprite)
{
  printf("next frame\n");
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
      // onEnd && onEnd();
    }
  }
}

void Sprite_SetSimulatorCallBack(Sprite *app, void (*func)(void *))
{
  app->simulatorCallBack = func;
}
void Sprite_simulatorCallBack(Sprite *sprite, void *charactor)
{
  if (sprite->simulatorCallBack != NULL)
  {
    sprite->simulatorCallBack(charactor);
  }
}

void Sprite_SetActionCallBack(Sprite *sprite, void (*func)(void *charactor, const char *actionName))
{
  sprite->actionCallBack = func;
}
void Sprite_DoAction(Sprite *sprite, void *charactor, const char *actionName)
{
  if (sprite->actionCallBack != NULL)
  {
    sprite->actionCallBack(charactor, actionName);
  }
}
