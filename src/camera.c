#include "camera.h"
#include <stdlib.h>

static Camera* camera = NULL;

bool Camera_Create() {
  camera = (Camera*)malloc(sizeof(Camera));
  if (camera == NULL) return false;
  camera->x = 0;
  camera->y = 0;
  return true;
}
void Camera_Destroy() {
  free(camera);
}

void Camera_Adjust() {
  if (camera->x < 0) camera->x = 0;
  if (camera->x > camera->maxWidth)
    camera->x = camera->maxWidth;
} 

void Camera_Correct() {
    // if (!baseSprite) return;
		// if (baseSprite.x - scrollManager.camera[0] > 220){
		// 	scrollManager.camera[0] = baseSprite.x - 220;
		// }
		// if (baseSprite.x - scrollManager.camera[0] < 130){
		// 	scrollManager.camera[0] = baseSprite.x - 130;
		// }
}

void Camera_SetMaxWidth(int maxWidth) {
  camera->maxWidth = maxWidth;
}

void Camera_MoveX(float x) {
  camera->x += x;
}

float Camera_GetX() {
  return camera->x;
}
void Camera_SetX(float x) {
  camera->x = x;
}
float Camera_GetY() {
  return camera->y;
}