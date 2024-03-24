#ifndef NEXUS_H
#define NEXUS_H 1

#include <time.h>
#include <sys/time.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

extern char *nexus_version_string;
extern int verbose;
extern int mainloopend;

void ShowHelp(void);
void ShowVersion(void);

#endif /* NEXUS_H */
