#ifndef Text_h
#define Text_h

#include <stdbool.h>
#include "TexturedRectangle.h"

typedef struct {
  char *str;
	float x;
	float y;
	int width;
	int wordWidth;
	int lineHeight;
	bool hidden;
  TexturedRectangle *texture;
} Text;

Text *Text_Create(const char *str, float x, float y);
void Text_Destroy(Text *text);

	/**
	 * 显示文字
	 */
void Text_Show (Text* text);
	/**
	 * 隐藏文字
	 */
void hide (Text* text);
	/**
	 * 重新显示文字
	 */
void Text_Reshow(Text* text);

#endif