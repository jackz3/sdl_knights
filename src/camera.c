#include "camera.h"
#include <stdlib.h>

Camera* Camera_Create() {
  Camera* cam = (Camera*)malloc(sizeof(Camera));
  cam->x = 0;
  cam->y = 0;
}
void Camera_Destroy(Camera* cam) {
  free(cam);
}

void Camera_Adjust(Camera* cam) {
  if (cam->x < 0) cam->x = 0;
  if (cam->x > cam->maxWidth)
    cam->x = cam->maxWidth;
} 

void Camera_Correct(Camera* cam) {
    // if (!baseSprite) return;
		// if (baseSprite.x - scrollManager.camera[0] > 220){
		// 	scrollManager.camera[0] = baseSprite.x - 220;
		// }
		// if (baseSprite.x - scrollManager.camera[0] < 130){
		// 	scrollManager.camera[0] = baseSprite.x - 130;
		// }
}

void Camera_SetMaxWidth(Camera* cam, int maxWidth) {
  cam->maxWidth = maxWidth;
}