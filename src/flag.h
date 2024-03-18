#ifndef FLAG_H
#define FLAG_H 1

#include <GL/gl.h>

struct Flag {
	GLfloat x, y, z;
	unsigned int width, height;
	unsigned long value;
	GLuint texture_id;
};
extern struct Flag flag01, flag02;

void FlagInit(void);
void FlagRender(void);
void FlagUpdate(void);

#endif /* FLAG_H */