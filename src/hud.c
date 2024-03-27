#include <GL/gl.h>

#include "camera.h"
#include "event.h"
#include "font.h"
#include "image.h"
#include "render.h"
#include "sky.h"
#include "terminal.h"
#include "window.h"
#include "hud.h"

GLuint compass_texture_id;

void HudInit(void) {
    GLubyte *data = ImageFromPNGFile(256, 256, "images/compass-256a.png");	
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &compass_texture_id);
	glBindTexture(GL_TEXTURE_2D, compass_texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(data);
}

void HudRender(void) {
    FontRender2D(BG_BLACK, 10, (int)winH-16-10, fps_text);
	if (terminal_visible)
		TerminalRender();
	if (!mouse_held)
		HudRenderCursor();
	HudRenderThrottle();
	HudRenderCompass();
	FontRender2D(BG_BLACK, winW-strlen(daylight_amount_text)*8, 16,
		daylight_amount_text);
}

void HudRenderCompass(void) {
	GLfloat half = winH/20.0;
	glPushMatrix();
	glTranslatef(winW-half, winH-half, 0.0);
	glBindTexture(GL_TEXTURE_2D, compass_texture_id);
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.3, 0.4);
	glTexCoord2f(0.0, 1.0);
	 glVertex2f(-half, -half);
	glTexCoord2f(0.0, 0.0);
	 glVertex2f(-half, half);
	glTexCoord2f(1.0, 0.0);
	 glVertex2f(half, half);
	glTexCoord2f(1.0, 1.0);
	 glVertex2f(half, -half);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.0);
	glRotatef(cam.rotation_angle, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	 glColor3f(0.4, 0.1, 0.1);
	 glVertex2f(-5.0, 0.0);
	 glVertex2f(0.0, half/2.0);
	 glVertex2f(5.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	 glColor3f(0.1, 0.1, 0.1);
	 glVertex2f(5.0, 0.0);
	 glVertex2f(0.0, -half/2.0);
	 glVertex2f(-5.0, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void HudRenderCursor(void) {
	glPushMatrix();
	glTranslatef((GLfloat)mouse_x, winH - (GLfloat)mouse_y, 0.0);
	glBegin(GL_LINES);
	glColor3f(0.7, 0.8, 0.9);
	glVertex2f(0.0, -10.0);
	glVertex2f(0.0, 10.0);
	glVertex2f(-10.0, 0.0);
	glVertex2f(10.0, 0.0);
	glEnd();
	glPopMatrix();
}

// Draw the throttle meter on the HUD
void HudRenderThrottle(void) {
	glPushMatrix();
	glTranslatef(winW-20.0, winH/2, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.7, 0.8);
	glVertex2f(0.0, 0.0);
	glVertex2f(10.0, 0.0);
	glVertex2f(10.0, cam.thr);
	glVertex2f(0.0, cam.thr);
	glEnd();
	glBegin(GL_LINE_STRIP);
	if (daylight_amount < 0.6)
		glColor3f(0.3, 0.4, 0.5);
	else
		glColor3f(0.1, 0.2, 0.3);
	glVertex2f(-1.0, -1.0);
	glVertex2f(11.0, -1.0);
	glVertex2f(11.0, 101.0);
	glVertex2f(-1.0, 101.0);
	glVertex2f(-1.0, -1.0);
	glEnd();
	glPopMatrix();
	FontRender2D(BG_BLACK, winW-strlen(cam.thr_text)*8, winH/2-20, cam.thr_text);
	FontRender2D(BG_BLACK, winW-strlen(cam.speed_text)*8, winH/2-40, cam.speed_text);
	FontRender2D(BG_BLACK, winW-strlen(cam.side_speed_text)*8, winH/2-60, cam.side_speed_text);
	FontRender2D(BG_BLACK, winW-strlen(cam.height_speed_text)*8, winH/2-80, cam.height_speed_text);
}
