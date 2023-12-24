#include <stdlib.h>
#include "StageManager.h"
#include "sdl_app.h"
#include "Lancelot.h"
#include "EntityManager.h"
#include "Keeper.h"
#include "Prophet.h"
#include "GameState.h"
#include "ResourceManager.h"

static Lancelot *lancelot;

static void stage1HandleInput(SDL_Event *event, const Uint8 *keysState)
{
    if (keysState == NULL)
    {
        return;
    }
    const Uint8 *state = keysState;
    KeyState *keyState = SDLApp_GetKeyState(); // &app->keyState;
    if (state[SDL_SCANCODE_W])
    {
        keyState->up = 1;
    }
    else
    {
        keyState->up = 0;
    }
    if (state[SDL_SCANCODE_S])
    {
        keyState->down = 1;
    }
    else
    {
        keyState->down = 0;
    }
    if (state[SDL_SCANCODE_A])
    {
        keyState->left = 1;
    }
    else
    {
        keyState->left = 0;
    }
    if (state[SDL_SCANCODE_D])
    {
        keyState->right = 1;
    }
    else
    {
        keyState->right = 0;
    }
    if (state[SDL_SCANCODE_J])
    {
        keyState->a = 1;
    }
    else
    {
        keyState->a = 0;
    }
    if (state[SDL_SCANCODE_K])
    {
        keyState->b = 1;
    }
    else
    {
        keyState->b = 0;
    }
}

static void stage1Update(Uint32 delta)
{
    EntityManager_Simulate(EntityManager_GetInstance());
    Lancelot_Controller(lancelot, SDLApp_GetKeyState());
}
static void stage1Render()
{
    EntityManager_Render(EntityManager_GetInstance());
}
static void stage1Destroy(Stage *stage)
{
    //   free(keeperPool);
    Lancelot_Destroy(lancelot);
    free(stage);
}

Stage *Stage_Create_1(const char *name)
{
    Stage *stage = (Stage *)malloc(sizeof(Stage));
    strncpy(stage->name, name, sizeof(stage->name) - 1);
    stage->name[sizeof(stage->name) - 1] = '\0';
    stage->handelInput = stage1HandleInput;
    stage->update = stage1Update;
    stage->render = stage1Render;
    stage->destroy = stage1Destroy;

    // playerPool.push(lancelot = new Lancelot({x: -3, y: 204, health:lancelotHealth || 80}));
    lancelot = Lancelot_Create(-3, 204, 80);
    GameState_AddKeeper(Keeper_Create(464, 164, "cask", "jewelrybag", "cask1"));
    GameState_AddKeeper(Keeper_Create(480, 196, "cask", "silverchest", "cask2"));
    GameState_AddKeeper(Keeper_Create(704, 155, "fence1", "goldchest", "fence1"));

    Prophet_Create(280, 165);

    ResourceManager_LoadMusic("bg", "./assets/sounds/bg.mp3");
    // Music_Play(ResourceManager_GetMusic(rm, "bg"), -1);
    return stage;
}