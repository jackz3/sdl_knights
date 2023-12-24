#ifndef camera_h
#define camera_h

#include <stdbool.h>

typedef struct {
  float x;
  float y;
  int maxWidth;
} Camera;

bool Camera_Create();
void Camera_Destroy();

void Camera_Adjust();

float Camera_GetX();
void Camera_SetX(float x);
float Camera_GetY();

void Camera_Correct();
void Camera_SetMaxWidth(int maxWidth);
void Camera_MoveX(float x);
#endif