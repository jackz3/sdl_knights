#ifndef camera_h
#define camera_h

typedef struct {
  float x;
  float y;
  int maxWidth;
} Camera;

Camera* Camera_Create();
void Camera_Destroy(Camera* cam);

void Camera_Adjust(Camera* cam);

void Camera_Correct(Camera* cam);
void Camera_SetMaxWidth(Camera*  cam, int maxWidth);
#endif