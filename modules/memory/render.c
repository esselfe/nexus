#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "nexus.h"

void MemoryRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Switch to 3D rendering (Scene)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, winW/winH, 0.01, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam.x, cam.y, cam.z,
            cam.lx, cam.ly, cam.lz,
            0.0, 1.0, 0.0);

	glTranslatef(-1.0, 0.0, 0.0);
    glColor3f(0.4, 0.5, 0.6);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0);
    glVertex3f(1.0, 3.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    SDL_GL_SwapWindow(window);
}

