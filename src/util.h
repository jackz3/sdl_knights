#ifndef util_h
#define util_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int rand_int(int min, int max);

char** string_split(const char* str, const char* delim, int* len);
char* toLowerCase(const char* str);

typedef struct ItemNode {
  void* item;
  struct ItemNode* next;
} ItemNode;

typedef struct {
  ItemNode* items;
  size_t itemCount;
} LinkedList;

LinkedList* LinkedList_Create();
void LinkedList_Destroy(LinkedList* list);
void LinkedList_Add(LinkedList* list, void* item);

typedef struct 
{
	char key[16];
	int value;
} KV;

int KV_GetValue(KV* kv, int count, char* key);


#endif