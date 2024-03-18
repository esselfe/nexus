#ifndef IMAGE_H
#define IMAGE_H 1

#include <GL/gl.h>

// Used to create textures
GLubyte *ImageFromPNGFile(unsigned int width, unsigned int height, char *filename);

#endif /* IMAGE_H */