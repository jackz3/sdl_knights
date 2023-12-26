#include "Text.h"
#include <string.h>
#include <math.h>
#include "sdl_app.h"
#include "util.h"

Text *Text_Create(const char *str, float x, float y)
{
  Text *text = malloc(sizeof(Text));
  int len = strlen(str);
  char *strCopy = malloc(sizeof(char) * (len + 1));
  strcpy(strCopy, toUpperCase(str));
  text->str = strCopy;
  text->x = x;
  text->y = y;
  text->width = 30;
  text->wordWidth = 8;
  text->lineHeight = 12;
  text->hidden = false;

  SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  text->texture = TexturedRectangle_Create(SDLApp_GetRenderer(), "./assets/images/font.png", rect);
  return text;
}

void Text_Destroy(Text *text)
{
  free(text->str);
  TexturedRectangle_Destroy(text->texture);
  free(text); 
}

static void drawChar(Text *text, char code, float sx, float sy)
{
  int offsetX = 650;
  int offsetY = 1;
  int gridX = 10;
  int gridY = 10;

  if (code >= 48 && code <= 57)
  {
    gridX = gridY = 8;
    offsetX = 48 * gridX - 2;
    offsetY = 135;
  }
  else if (code == 32)
  {
    code = 94;
  }
  else if (code == 44)
  { //,
    code = 93;
  }
  else if (code == 46)
  { //.
    code = 91;
  }
  else if (code == 33)
  { //!
    code = 92;
  }
  else if (code == 40)
  { //(
    gridX = 8;
    gridY = 8;
    offsetX = 40 * gridX - 357;
    offsetY = 163;
  }
  else if (code == 41)
  { //)
    gridX = 8;
    gridY = 8;
    offsetX = 40 * gridX - 355;
    offsetY = 163;
  }
  else if (code == 58)
  { //)
    gridX = 8;
    gridY = 8;
    offsetX = 58 * gridX - 502;
    offsetY = 163;
  }
  else if (code == 47)
  { //)
    gridX = 8;
    gridY = 8;
    offsetX = 47 * gridX - 413;
    offsetY = 163;
  }
  else if (code < 65)
  {
    code = 65;
  }
  else if (code > 90)
  {
    code = 90;
  }

  TexturedRectangle_SetSrcPosition(text->texture,
    code * gridX - offsetX, offsetY
  );
  TexturedRectangle_SetSrcDimension(text->texture, gridX, gridY);
  TexturedRectangle_Render(text->texture,
    text->x + sx * text->wordWidth, text->y + sy * text->lineHeight,
  gridX, gridY);
}

void Text_Show(Text *text)
{
  if (text->hidden)
    return;
  for (int n = 0, m = strlen(text->str); n < m; n++)
  {
    drawChar(text, text->str[n], n % text->width, floor(n / text->width));
  }
}
void hide(Text *text)
{
  text->hidden = true;
}
void Text_Reshow(Text *text)
{
  text->hidden = false;
  Text_Show(text);
}
