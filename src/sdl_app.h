#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include "camera.h"

typedef struct {
    int up;
    int down;
    int left;
    int right;
    int a;
    int b;
} KeyState;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int maxFrameRate;
    int gameIsRunning;
    int mouseX;
    int mouseY;
    int width;
    int height;
    int scale;
    void (*eventCallback)(void);
    void (*updateCallback)(Uint32 delta);
    void (*renderCallback)(void);
    SDL_TimerID* timers;
    int timerCount;
    Camera* cam;
    KeyState keyState;
} SDLApp;

SDLApp* SDLApp_Create(Uint32 subsystemFlags, const char* title, int x, int y, int w, int h, int scale);
void SDLApp_Destroy();
void SDLApp_SetEventCallback(void (*func)(void));
void SDLApp_SetUpdateCallback(void (*func)(Uint32 delta));
void SDLApp_SetRenderCallback(void (*func)(void));
void SDLApp_RunLoop();
void SDLApp_SetMaxFrameRate(int frameRate);
SDL_Renderer* SDLApp_GetRenderer();
int SDLApp_GetMouseX();
int SDLApp_GetMouseY();
int SDLApp_GetWindowWidth();
int SDLApp_GetWindowHeight();
void SDLApp_StopAppLoop();
SDL_TimerID SDLApp_AddTimer(Uint32 delay, SDL_TimerCallback callback, void* param);
SDL_TimerID SDLApp_AddRecurringTimer(Uint32 interval, SDL_TimerCallback callback, void* param);
void SDLApp_RemoveTimer(SDL_TimerID id);
KeyState* SDLApp_GetKeyState();
#endif