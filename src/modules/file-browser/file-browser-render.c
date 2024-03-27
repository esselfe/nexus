#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "nexus.h"
#include "camera.h"
#include "event.h"
#include "floor.h"
#include "font.h"
#include "hud.h"
#include "render.h"
#include "sky.h"
#include "terminal.h"
#include "window.h"
#include "file-browser.h"

void FileBrowserRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Switch to 3D rendering (Scene)
	if (render)
		RenderSet3DView();
	else {
		GLint viewport[4] = { 0, winH, winW, -winH };
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPickMatrix(mouse_x, mouse_y, 1.0, 1.0, viewport);
		glScalef(-1.0, 1.0, 1.0);
		gluPerspective(60.0, winW/winH, 0.01, 1500.0);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(cam.x, cam.y, cam.z,
				cam.lx, cam.ly, cam.lz,
				0.0, 1.0, 0.0);
	}

	if (render) { // Do not render if doing picking
		SkyRender();
		FloorRender();
	}

	struct FileBrowserListEntry *entry = file_browser_list.first_entry;
	if (entry == NULL)
		return;

	while (1) {
		glPushMatrix();
		glTranslatef(0.0, 0.2*(entry->rank-1), 0.0);
		glColor3f(0.2, 0.2, 0.2);
		if (!render)
			glPushName(entry->selectid->id);
		glBegin(GL_QUADS);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 0.2);
		glVertex2f(1.0, 0.2);
		glVertex2f(1.0, 0.0);
		glEnd();
		
		if (entry == file_browser_selected_entry) {
			glColor3f(0.8, 0.5, 0.3);
			glBegin(GL_LINE_STRIP);
			glVertex3f(0.0, 0.0, 0.1);
			glVertex3f(0.0, 0.2, 0.1);
			glVertex3f(1.0, 0.2, 0.1);
			glVertex3f(1.0, 0.0, 0.1);
			glVertex3f(0.0, 0.0, 0.1);
			glEnd();
		}
		glPopMatrix();
		if (render) {
			if (entry->type == ENTRY_TYPE_DIRECTORY)
				FontRender(BG_BLACK, FG_BLUE, 0.0, 0.2*(entry->rank-1),
					0.1, entry->name);
			else if (entry->type == ENTRY_TYPE_EXECUTABLE)
				FontRender(BG_BLACK, FG_GREEN, 0.0, 0.2*(entry->rank-1),
					0.1, entry->name);
			else if (entry->type == ENTRY_TYPE_FILE)
				FontRender(BG_BLACK, FG_NONE, 0.0, 0.2*(entry->rank-1),
					0.1, entry->name);
			else if (entry->type == ENTRY_TYPE_UNKNOWN)
				FontRender(BG_BLACK, FG_NONE, 0.0, 0.2*(entry->rank-1),
					0.1, entry->name);
		}
		else
			glPopName();

		if (entry->next != NULL)
			entry = entry->next;
		else
			break;
	}

	if (render) {
		// Switch to 2D rendering (HUD)
		RenderSet2DView();

		HudRender();

		SDL_GL_SwapWindow(window);
	}
}

