#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "nexus.h"
#include "event.h"
#include "floor.h"
#include "font.h"
#include "hud.h"
#include "render.h"
#include "sky.h"
#include "terminal.h"
#include "window.h"

void EditorRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Switch to 3D rendering (Scene)
	RenderSet3DView();

	SkyRender();
	FloorRender();

	glPushMatrix();
	glTranslatef(-1.5, 0.0, 0.0);
	glColor3f(0.4, 0.5, 0.6);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 3.0, 0.0);
	glVertex3f(3.0, 3.0, 0.0);
	glVertex3f(3.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();

	// Switch to 2D rendering (HUD)
	RenderSet2DView();

	HudRender();

	SDL_GL_SwapWindow(window);
}

