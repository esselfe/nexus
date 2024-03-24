#include <stdio.h>
#include <GL/gl.h>

#include "nexus.h"
#include "render.h"
#include "file-browser.h"

GLuint file_browser_select_buffer[100];

void FileBrowserPickingCheck(void) {
	glSelectBuffer(100, file_browser_select_buffer);
	glRenderMode(GL_SELECT);
	render = 0;
	FileBrowserRender();
	render = 1;
	int hits = glRenderMode(GL_RENDER);
	
	if (hits)
		file_browser_selected_entry = 
			FileBrowserListEntryBySelectID(file_browser_select_buffer[3]);
	else
		file_browser_selected_entry = NULL;
}

