#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "Sound.h"
#include "Music.h"
#include "DynamicText.h"

typedef struct ImgNode {
    char path[128];
    SDL_Surface* surface;
    struct ImgNode* next;
} ImgNode;

typedef struct FontNode {
    char name[32];
    char path[128];
    DynamicText* font;
    struct FontNode* next;
} FontNode;

typedef struct SoundNode {
    char name[32];
    char path[128];
    Sound* sound;
    struct SoundNode* next;
} SoundNode;

typedef struct MusicNode {
    char name[32];
    char path[128];
    Music* music;
    struct MusicNode* next;
} MusicNode;

typedef struct {
    ImgNode* images;
    int imgCount;
    FontNode* fonts;
    int fontCount;
    SoundNode* sounds;
    int soundCount;
    MusicNode* musicList;
    int musicCount;
} ResourceManager;

bool ResourceManager_Init();
SDL_Surface* ResourceManager_GetSurface(const char* filepath);
void ResourceManager_Destroy();
bool ResourceManager_LoadFont(const char* name, const char* path);
DynamicText* ResourceManager_GetFont(const char* name);
bool ResourceManager_LoadSound(const char* name, const char* path);
Sound* ResourceManager_GetSound(const char* name);
bool ResourceManager_LoadMusic(const char* name, const char* path);
Music* ResourceManager_GetMusic(const char* name);

#endif