#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "nexus.h"

void BrowserRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Switch to 3D rendering (Scene)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, winW/winH, 0.01, 1500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.x, cam.y, cam.z,
			cam.lx, cam.ly, cam.lz,
			0.0, 1.0, 0.0);

	SkyRender();
	FloorRender();

	struct BrowserListEntry *entry = browser_list.first_entry;
	if (entry == NULL)
		return;

	while (1) {
		glPushMatrix();
		glTranslatef(0.0, 0.2*(entry->rank-1), 0.0);
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_QUADS);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 1.0);
		glVertex2f(1.0, 1.0);
		glVertex2f(1.0, 0.0);
		glEnd();
		glPopMatrix();
		FontRender(0.0, 0.2*(entry->rank-1), 0.1, entry->name);

		if (entry->next != NULL)
			entry = entry->next;
		else
			break;
	}

	// Switch to 2D rendering (HUD)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winW, 0.0, winH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	FontRender2D(10, (int)winH-16-10, fps_text);

	if (terminal_visible)
		TerminalRender();
	
	RenderThrottle();

	SDL_GL_SwapWindow(window);
}

