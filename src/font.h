#ifndef FONT_H
#define FONT_H 1

#include <GL/gl.h>

// Text background and foreground colors
#define BG_NONE    0
#define BG_BLACK   1
#define BG_GRAY    2
#define BG_GREY    2
#define FG_NONE    0
#define FG_BLUE    1
#define FG_GREEN   2

void FontInit(void);
// 3D-positioned scene text
void FontRender(int bgcolor, int fgcolor, GLfloat x, GLfloat y, GLfloat z, char *text);
// HUD text
void FontRender2D(int bgcolor, int x, int y, char *text);

#endif /* FONT_H */