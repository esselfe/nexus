#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "nexus.h"

void BrowserRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Switch to 3D rendering (Scene)
	RenderSet3DView();

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
	RenderSet2DView();

	FontRender2D(10, (int)winH-16-10, fps_text);

	if (terminal_visible)
		TerminalRender();
	if (!mouse_held)
		RenderCursor();
	
	RenderThrottle();
	RenderCompass();

	SDL_GL_SwapWindow(window);
}

