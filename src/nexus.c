#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "nexus.h"

char *nexus_version_string = "0.1.2";
int mainloopend;
int init_done;
SDL_DisplayMode display_mode;
SDL_Window *window;
SDL_GLContext context;
GLfloat winX = 100.0, winY = 40.0, winW = 800.0, winH = 600.0;
char window_title[1024];
unsigned int fps;
time_t t0, tprev;
struct timeval tv0, tv_prev, tv_diff;
char *fps_text;

void NexusExit(void) {
	// Prevent saving zeroes if exit() was called before
	// the score was loaded.
	if (init_done)
		ElementScoreSave();
	
	printf("\nnexus exited\n");
}

void tvdiff(struct timeval *tv_start, struct timeval *tv_end, struct timeval *tv_diff2) {
	tv_diff2->tv_sec = 0; // to fix
	if (tv_start->tv_sec == tv_end->tv_sec) {
		tv_diff2->tv_usec = tv_end->tv_usec - tv_start->tv_usec;
	}
	else {
		tv_diff2->tv_usec = tv_end->tv_usec + (1000000-tv_start->tv_usec);
		if (tv_diff2->tv_usec >= 1000000) {
			++tv_diff2->tv_sec;
			tv_diff2->tv_usec -= 1000000;
		}
	}
}

int main(int argc, char **argv) {
	printf("nexus %s started\n", nexus_version_string);

	atexit(NexusExit);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf ("nexus: SDL_Init() failed.\n");
		exit(1);
	}

	int major, minor;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	printf("Using OpenGL %d.%d\n", major, minor);

	sprintf(window_title, "nexus %s", nexus_version_string);
	window = SDL_CreateWindow(window_title, winX, winY + 30, winW, winH,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		printf("nexus: Cannot create SDL2/GL context. Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	// needs a context
	printf("OpenGL %s installed\n", glGetString(GL_VERSION));

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf ("nexus: Cannot initialize GLEW.\n");
		SDL_GL_DeleteContext(context);
		SDL_Quit();
		exit(1);
	}

	fps_text = malloc(20);
	sprintf(fps_text, "0 fps");

	StateSet(STATE_MAIN);
	EventInit();
	DeltaInit();
	CameraInit();
	RenderInit();
	FontInit();
	ElementInit();
	FlagInit();
	SkyInit();
	BrowserListLoad(get_current_dir_name());
	
	init_done = 1;

	tprev = time(NULL);
	gettimeofday(&tv_prev, NULL);
	while (!mainloopend) {
		++fps;
		EventFunc();
		DeltaFunc();
		CameraMove();
		if (render) RenderFunc();
	}

	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

