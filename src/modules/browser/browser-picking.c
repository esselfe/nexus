#include <GL/gl.h>

#include "nexus.h"

GLuint browser_select_buffer[100];

void BrowserPickingCheck(void) {
	glSelectBuffer(100, browser_select_buffer);
	glRenderMode(GL_SELECT);
	render = 0;
	BrowserRender();
	render = 1;
	int hits = glRenderMode(GL_RENDER);
	
	if (hits)
		browser_selected_entry = BrowserListEntryByRank(browser_select_buffer[3]);
	else
		browser_selected_entry = NULL;
}

