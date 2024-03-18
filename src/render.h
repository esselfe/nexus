#ifndef RENDER_H
#define RENDER_H 1

#include <GL/gl.h>

extern GLfloat light_ambient[];
extern GLfloat light_diffuse[];
extern GLfloat light_specular[];
extern GLfloat light_position[];
extern int render; // Used for ignoring some calls when picking

void Render(void);
void RenderCompass(void);
void RenderCursor(void);
// Modules are supposed to associate this handler to their function
extern void (*RenderFunc)(void);
void RenderInit(void);
void RenderSet2DView(void);
void RenderSet3DView(void);
// Draw the throttle meter on the HUD
void RenderThrottle(void);

#endif /* RENDER_H */