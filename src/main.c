#define SDL_MAIN_HANDLED
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdio.h>
#include "util.h"
#include "sdl_app.h"
#include "TexturedRectangle.h"
#include "GameEntity.h"
#include "DynamicText.h"
#include "ResourceManager.h"
#include "Music.h"
#include "Sound.h"
#include "config.h"
#include "Background.h"
#include "camera.h"
#include "Prophet.h"

// render manager
// res loader
// scroll manager

SDLApp *app;

BG* farBg;
BG* midBg;
BG* nearBg;
Prophet* prophet;

Camera* cam;

typedef struct
{
    int player1Score;
    int player2Score;
    int servingPlayer;
    int winningPlayer;
} GameState;

GameState *gameState;

// Callback function for handling events
void HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_WINDOWEVENT_CLOSE)
        {
            SDLApp_StopAppLoop(app);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                SDLApp_StopAppLoop(app);
                break;
            case SDLK_RETURN:
                break;
            }
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP])
    {
    }
    else if (state[SDL_SCANCODE_DOWN])
    {
    }
    else{
    } 
    if (state[SDL_SCANCODE_W])
    {
    }
    else if (state[SDL_SCANCODE_S])
    {
    }
    if (state[SDL_SCANCODE_LEFT]) {
        cam->x--;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        cam->x += 2;
        printf("left %f \n", cam->x);
    }
}

// Update callback
void HandleUpdate(Uint32 delta)
{
    printf("updating\n");
    Sprite_NextFrame(prophet->entity->m_sprite, prophet);
}

// Handle the rendering of the game entities
void HandleRendering()
{
    ResourceManager *rm = ResourceManager_GetInstance();
    Camera_Adjust(cam);
    float sx = cam->x * 0.7;
    TexturedRectangle_SetSrcPosition(farBg->m_texture, sx, 0);
    BG_Render(farBg);
    Camera_Adjust(cam);
    TexturedRectangle_SetSrcPosition(midBg->m_texture, cam->x, 0);
    BG_Render(midBg);
    printf("rendering\n");
    GameEntity_RenderSprite(prophet->entity);

    Camera_Adjust(cam);
    TexturedRectangle_SetSrcPosition(nearBg->m_texture, cam->x, 0);
    BG_Render(nearBg);
}

Uint32 my_callbackfunc(Uint32 interval, void *param)
{
    printf("Fun score updated from: %s:s s\n", (const char *)param);
    return 0;
}

// Entry point of the program
int main(int argc, char *argv[])
{
    // Setup the SDLApp
    const char *title = "SDL2_Pong";
    app = SDLApp_Create(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER, title, 80, 80, VIRTUALWIDTH * SCALE, VIRTUALHEIGHT * SCALE);
    SDLApp_SetMaxFrameRate(app, 16);

    cam = Camera_Create();
    Camera_SetMaxWidth(cam, 800);
    ResourceManager *rm = ResourceManager_GetInstance();
    ResourceManager_LoadFont(rm, "peaberry", "./assets/fonts/PeaberryMono.ttf");

    farBg = BG_Create(0, 0, VIRTUALWIDTH * SCALE, VIRTUALHEIGHT * SCALE);
    SDL_Rect srcRect = {0, 0, VIRTUALWIDTH, VIRTUALHEIGHT};
    BG_AddTexture(farBg, app->renderer, "./assets/images/stage1_1_b.png", &srcRect);
    midBg = BG_Create(0, 0, VIRTUALWIDTH * SCALE, VIRTUALHEIGHT * SCALE);
    BG_AddTexture(midBg, app->renderer, "./assets/images/stage1_1_m.png", &srcRect);
    nearBg = BG_Create(0, 0, VIRTUALWIDTH * SCALE, VIRTUALHEIGHT * SCALE);
    BG_AddTexture(nearBg, app->renderer, "./assets/images/stage1_1_f.png", &srcRect);

    ResourceManager_LoadSound(rm, "bonus", "./assets/sounds/bonus.mp3");
    // ResourceManager_LoadMusic(rm, "bg", "./assets/sounds/bg.mp3");
    // Music_Play(ResourceManager_GetMusic(rm, "bg"), -1);

    prophet = Prophet_Create(280, 165);
    printf("created\n");

    // Setup the Game State
    gameState = (GameState *)malloc(sizeof(GameState));
    gameState->player1Score = 0;
    gameState->player2Score = 0;
    gameState->servingPlayer = 1;
    gameState->winningPlayer = 0;

    // Set callback functions
    SDLApp_SetEventCallback(app, HandleEvents);
    SDLApp_SetUpdateCallback(app, HandleUpdate);
    SDLApp_SetRenderCallback(app, HandleRendering);

    // Add some timers (for demonstration purpose)
    // SDLApp_AddTimer(app, 2000, my_callbackfunc, (char *)"timer called");
    SDLApp_RunLoop(app);
    // Clean up our application
    SDLApp_Destroy(app);
    ResourceManager_Destroy(rm);
    Prophet_Destroy(prophet);
    // EntityManager_DeleteAll(entityMgr);
    return 0;
}