#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "nexus.h"
#include "delta.h"
#include "event.h"
#include "floor.h"
#include "font.h"
#include "render.h"
#include "sky.h"
#include "terminal.h"
#include "element.h"

int render = 1;
GLfloat element_mat_amb_diff[4];

void ElementRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Switch to 3D rendering (Scene)
	RenderSet3DView();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	if (daylight_amount > 0.4) {
		element_mat_amb_diff[0] = daylight_amount;
		element_mat_amb_diff[1] = daylight_amount;
		element_mat_amb_diff[2] = daylight_amount;
		element_mat_amb_diff[3] = 1.0;
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
            element_mat_amb_diff);

	SkyRender();
	FloorRender();
	
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
        
	struct Element *el = element_root_list.first_element;
	if (el != NULL) {
		while (1) {
			glBindTexture(GL_TEXTURE_2D, el->texture_id);
			glPushMatrix();
			glTranslatef(el->x, el->y, el->z);
			glScalef(1.0, -1.0, 1.0);
			glRotatef(delta, 0.0, 1.0, 0.0);
			glBegin(GL_POLYGON);
			glColor4f(0.5, 0.5, 0.5, 1.0);
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
	}
	glEnable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);

	// Switch to 2D rendering (HUD)
	RenderSet2DView();

	FontRender2D(BG_BLACK, 10, (int)winH-16-10, fps_text);

	char text[128];
	sprintf(text, "%lu waste", total_waste);
	FontRender2D(BG_GREY, 10, (int)winH-16-30, text);
	
	sprintf(text, "%lu battery", total_battery);
	FontRender2D(BG_GREY, 10, (int)winH-16-50, text);

	sprintf(text, "%lu copper", total_copper);
	FontRender2D(BG_GREY, 10, (int)winH-16-70, text);
	
	sprintf(text, "%lu gold", total_gold);
	FontRender2D(BG_GREY, 10, (int)winH-16-90, text);
	
	sprintf(text, "%lu iron", total_iron);
	FontRender2D(BG_GREY, 10, (int)winH-16-110, text);
	
	sprintf(text, "%lu magnet", total_magnet);
	FontRender2D(BG_GREY, 10, (int)winH-16-130, text);
	
	sprintf(text, "%lu rock", total_rock);
	FontRender2D(BG_GREY, 10, (int)winH-16-150, text);
	
	sprintf(text, "%lu rubber", total_rubber);
	FontRender2D(BG_GREY, 10, (int)winH-16-170, text);
	
	sprintf(text, "%lu silver", total_silver);
	FontRender2D(BG_GREY, 10, (int)winH-16-190, text);
	
	sprintf(text, "%lu wood", total_wood);
	FontRender2D(BG_GREY, 10, (int)winH-16-210, text);
	
	sprintf(text, "%lu elements", element_root_list.total_elements);
	FontRender2D(BG_GREY, 10, (int)winH-16-230, text);
	
	if (terminal_visible)
		TerminalRender();
	if (!mouse_held)
		RenderCursor();

	RenderThrottle();
	RenderCompass();
	FontRender2D(BG_BLACK, winW-strlen(daylight_amount_text)*8, 16,
		daylight_amount_text);

	SDL_GL_SwapWindow(window);
}

