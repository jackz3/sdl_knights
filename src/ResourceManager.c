#include "ResourceManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <string.h>

static ResourceManager* manager = NULL;
bool ResourceManager_Init() {
    if (manager == NULL) {
        manager = (ResourceManager*)malloc(sizeof(ResourceManager));
        if (manager == NULL) {
          printf("create res manager fail!\n");
          return false;
        }
        manager->images = NULL;
        manager->imgCount = 0;
        manager->fonts = NULL;
        manager->fontCount = 0;
        manager->sounds = NULL;
        manager->soundCount = 0;
        manager->musicList = NULL;
        manager->musicCount = 0;

        int flags = IMG_INIT_PNG;
        int initStatus = IMG_Init(flags);
        if((initStatus & flags) != flags){
            printf("SDL2_Image format not available \n");
            return false;
        }
        // Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
            printf("Audio library not working: %s\n", Mix_GetError());
            return false;
        }
    }
    return true;
}

SDL_Surface* ResourceManager_GetSurface(const char* filepath) {
    ImgNode* node = manager->images;
    while (node) {
        if (strcmp(node->path, filepath) == 0) {
            return node->surface;
        }
        node = node->next;
    }
    const char ch = '.';
    char *ret;
    ret = strrchr(filepath, ch);
    SDL_Surface* surface = NULL;
    if (strcmp(ret, ".bmp") == 0) {
        surface = SDL_LoadBMP(filepath);
    } else if(strcmp(ret, ".png") == 0) {
        surface = IMG_Load(filepath);
    }
    if (surface != NULL) {
        ImgNode* newNode = malloc(sizeof(ImgNode));
        strncpy(newNode->path, filepath, sizeof(newNode->path));
        newNode->surface = surface;
        newNode->next = manager->images;

        manager->images = newNode;
        manager->imgCount++;
        return surface;
    }
    return NULL;
}

bool ResourceManager_LoadMusic(const char* name, const char* path) {
    MusicNode* node = manager->musicList;
    while (node)
    {
        if(strcmp(node->name, name) == 0) {
            return true;
        }
        node = node->next;
    }
    Music* music = Music_Create(path);
    if (music != NULL) {
        MusicNode* newNode = malloc(sizeof(SoundNode));
        strncpy(newNode->name, name, sizeof(newNode->name));
        strncpy(newNode->path, path, sizeof(newNode->path));
        newNode->music = music;
        newNode->next = manager->musicList;

        manager->musicList = newNode;
        manager->musicCount++;
        return true;
    } else {
        printf("Could not load music: %s\n", Mix_GetError());
        return false;
    }
}
Music* ResourceManager_GetMusic(const char* name) {
    MusicNode* node = manager->musicList;
    while (node) {
        if (strcmp(node->name, name) == 0) {
            return node->music;
        }
        node = node->next;
    }
    return NULL;
}

bool ResourceManager_LoadSound(const char* name, const char* path) {
    SoundNode* node = manager->sounds;
    while (node)
    {
        if(strcmp(node->name, name) == 0) {
            return true;
        }
        node = node->next;
    }
    Sound* sound = Sound_Create(path);
    if (sound != NULL) {
        SoundNode* newNode = malloc(sizeof(SoundNode));
        strncpy(newNode->name, name, sizeof(newNode->name));
        strncpy(newNode->path, path, sizeof(newNode->path));
        newNode->sound = sound;
        newNode->next = manager->sounds;

        manager->sounds = newNode;
        manager->soundCount++;
        return true;
    } else {
        printf("Could not load music: %s\n", Mix_GetError());
        return false;
    }
}

Sound* ResourceManager_GetSound(const char* name) {
    SoundNode* node = manager->sounds;
    while (node) {
        if (strcmp(node->name, name) == 0) {
            return node->sound;
        }
        node = node->next;
    }
    return NULL;
}

bool ResourceManager_LoadFont(const char* name, const char* path) {
    FontNode* node = manager->fonts;
    while (node) {
        if (strcmp(node->name, name) == 0) {
            return true;
        }
        node = node->next;
    }
    DynamicText* text = DynamicText_Create(path, 24);
    if (text != NULL) {
        FontNode* newNode = malloc(sizeof(FontNode));
        strncpy(newNode->name, name, sizeof(newNode->name));
        strncpy(newNode->path, path, sizeof(newNode->path));
        newNode->font = text;
        newNode->next = manager->fonts;

        manager->fonts= newNode;
        manager->fontCount++;
        return true;
    }

    return false;
}

DynamicText* ResourceManager_GetFont(const char* name) {
    FontNode* node = manager->fonts;
    while (node) {
        if (strcmp(node->name, name) == 0) {
            return node->font;
        }
        node = node->next;
    }
    return NULL;
}

void ResourceManager_Destroy() {
    if (manager == NULL) {
        return;
    }
    while (manager->images)
    {
        ImgNode* node = manager->images;
        manager->images = node->next;
        SDL_FreeSurface(node->surface);
        free(node);
    }
    manager->images = NULL;
    manager->imgCount = 0;

    while (manager->fonts) {
        FontNode* node = manager->fonts;
        manager->fonts = node->next;
        DynamicText_Destroy(node->font);
        free(node);
    }
    manager->fonts = NULL;
    manager->fontCount = 0;

    while (manager->sounds) {
        SoundNode* node = manager->sounds;
        manager->sounds = node->next;
        Sound_Destroy(node->sound);
        free(node);
    }
    manager->sounds = NULL;
    manager->soundCount = 0;

    while (manager->musicList) {
        MusicNode* node = manager->musicList;
        manager->musicList = node->next;
        Music_Destroy(node->music);
        free(node);
    }
    manager->musicList = NULL;
    manager->musicCount = 0;
}