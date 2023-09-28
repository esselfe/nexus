#include <stdio.h>
#include <unistd.h>
#include <GL/gl.h>

#include "nexus.h"

void BrowserInit(void) {
	if (verbose) printf("Initializing browser\n");
	
	glInitNames();
	glPushName(0);
	
	glSelectBuffer(100, browser_select_buffer);
	
	BrowserListLoad(get_current_dir_name());
}

