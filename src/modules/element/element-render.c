#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "nexus.h"

int render = 1;

void ElementRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	// Switch to 3D rendering (Scene)
	RenderSet3DView();

	SkyRender();
	FloorRender();
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	struct Element *el = element_root_list.first_element;
	while (1) {
		glBindTexture(GL_TEXTURE_2D, el->texture_id);
		glPushMatrix();
		glTranslatef(el->x, el->y, el->z);
		glRotatef(delta, 0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		glColor3f(0.4, 0.5, 0.6);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-el->width/2, -el->height/2, 0.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-el->width/2, el->height/2, 0.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(el->width/2, el->height/2, 0.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(el->width/2, -el->height/2, 0.0);
		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		if (el->next != NULL)
			el = el->next;
		else
			break;
	}

	// Switch to 2D rendering (HUD)
	RenderSet2DView();

	FontRender2D(10, (int)winH-16-10, fps_text);

	char text[128];
	sprintf(text, "%lu waste", total_waste);
	FontRender2D(10, (int)winH-16-26, text);
	
	sprintf(text, "%lu iron", total_iron);
	FontRender2D(10, (int)winH-16-42, text);
	
	sprintf(text, "%lu wood", total_wood);
	FontRender2D(10, (int)winH-16-58, text);
	
	sprintf(text, "%lu magnet", total_magnet);
	FontRender2D(10, (int)winH-16-74, text);
	
	sprintf(text, "%lu rock", total_rock);
	FontRender2D(10, (int)winH-16-90, text);

	if (terminal_visible)
		TerminalRender();
	if (!mouse_held)
		RenderCursor();

	RenderThrottle();

	SDL_GL_SwapWindow(window);
}

