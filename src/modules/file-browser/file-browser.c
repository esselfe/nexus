#include <stdio.h>
#include <unistd.h>
#include <GL/gl.h>

#include "nexus.h"
#include "file-browser.h"

void FileBrowserInit(void) {
	if (verbose) printf("Initializing file browser\n");
	
	glSelectBuffer(100, file_browser_select_buffer);
	
	FileBrowserListLoad(get_current_dir_name());
}

