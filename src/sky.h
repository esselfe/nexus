#ifndef SKY_H
#define SKY_H 1

#include <GL/gl.h>

// The sky is a box without bottom or top, only 4 of 6 sides
extern GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4;
extern GLfloat daylight_amount;
extern char daylight_amount_text[10];
extern int daylight_enabled;
extern int daylight_up;

void SkyInit(void);
void SkyRender(void);

#endif /* SKY_H */