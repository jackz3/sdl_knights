#define SDL_MAIN_HANDLED
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdio.h>
#include "util.h"
#include "sdl_app.h"
#include "TexturedRectangle.h"
#include "DynamicText.h"
#include "ResourceManager.h"
#include "EntityManager.h"
#include "Music.h"
#include "Sound.h"
#include "config.h"
#include "Background.h"
#include "camera.h"
#include "StageManager.h"
#include "GameState.h"


// Callback function for handling events
void HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_WINDOWEVENT_CLOSE)
        {
            SDLApp_StopAppLoop();
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                SDLApp_StopAppLoop();
                break;
            case SDLK_RETURN:
                break;
            }
        }
        Stage_HandleInput(&event, NULL);
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
		Stage_HandleInput(&event, state);
    if (state[SDL_SCANCODE_UP])
    {
    }
    else if (state[SDL_SCANCODE_DOWN])
    {
    }
    else{
    } 
    if (state[SDL_SCANCODE_LEFT]) {
        Camera_MoveX(-1);
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        Camera_MoveX(2);
        printf("left %f \n", Camera_GetX());
    }
}

// Update callback
void HandleUpdate(Uint32 delta)
{
    printf("updating\n");
    Stage_Update(delta);
}

// Handle the rendering of the game entities
void HandleRendering()
{
    BG_RenderFar();
    printf("rendering\n");
    Stage_Render();

    LinkedList *textPool = GameState_GetTextPool();
    ItemNode *node = textPool->items;
    while (node)
    {
        Text* text = (Text*)node->item;
        Text_Show(text);
        node = node->next;
    }
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
    const char *title = "SDL2 Knights_Of_Round";
    SDLApp_Create(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER, title, 80, 80, VIRTUALWIDTH, VIRTUALHEIGHT, SCALE);
    SDLApp_SetMaxFrameRate(16);

    Camera_Create();
    Camera_SetMaxWidth(800);
    ResourceManager_Init();
    ResourceManager_LoadFont("peaberry", "./assets/fonts/PeaberryMono.ttf");

    BG_Init();

    char soundList[][32] = {
			"powerwave",
			"smoke",
			"lightslash",
			"heavyslash",
			"floor",
			"doubleslash",
			"blood",
			"wound",
			"bonus",
			"clank",
			"cask",
			"victory",
			"armorflash",
			"boss1",
			"boss2",
			"death",
			"death2",
			"death3",
			"death4",
			"scorn",
			"victory2",
			"victory3",
			"bonusfood",
			"revert"
		};
    for (int i = 0, l = sizeof(soundList) / sizeof(soundList[0]); i < l; i++) {
        char path[128];
        sprintf(path, "./assets/sounds/%s.mp3", soundList[i]); 
        ResourceManager_LoadSound(soundList[i], path);
    }

    GameState_Init();
    StageManager_Init();

    // Set callback functions
    SDLApp_SetEventCallback(HandleEvents);
    SDLApp_SetUpdateCallback(HandleUpdate);
    SDLApp_SetRenderCallback(HandleRendering);

    // Add some timers (for demonstration purpose)
    // SDLApp_AddTimer(app, 2000, my_callbackfunc, (char *)"timer called");
    SDLApp_RunLoop();
    // Clean up our application
    SDLApp_Destroy();
    ResourceManager_Destroy();
	  EntityManager_DeleteAll(EntityManager_GetInstance());
    return 0;
}