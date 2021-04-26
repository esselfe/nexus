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

char *nexus_version_string = "0.0.9";
int mainloopend;

SDL_DisplayMode display_mode;
SDL_Window *window;
SDL_GLContext context;
GLfloat winX = 100.0, winY = 40.0, winW = 800.0, winH = 600.0;
GLfloat flagX, flagY, flagZ;
char window_title[1024];
GLfloat delta;
unsigned int fps;
char *fps_text;
struct Camera cam;

void NexusExit(void) {
	printf("\nnexus exited\n");
}

void tvdiff(struct timeval *tv_start, struct timeval *tv_end, struct timeval *tv_diff) {
	tv_diff->tv_sec = tv_end->tv_sec - tv_start->tv_sec;

	if (tv_end->tv_usec >= tv_start->tv_usec)
		tv_diff->tv_usec = tv_end->tv_usec - tv_start->tv_usec;
	else
		tv_diff->tv_usec = tv_end->tv_usec + (1000000-tv_start->tv_usec);
	
	if (tv_diff->tv_usec >= 1000000) {
		++tv_diff->tv_sec;
		tv_diff->tv_usec -= 1000000;
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
	SDL_WarpMouseInWindow(window, winW / 2, winH / 2);

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

	cam.x = 0.0;
	cam.y = 2.0;
	cam.z = 10.0;
	cam.lx = 0.0;
	cam.ly = 2.0;
	cam.lz = 0.0;

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport((GLint)0, (GLint)0, (GLsizei)winW, (GLsizei)winH);

	fps_text = malloc(128);
	sprintf(fps_text, "0 fps");

	RenderFunc = Render;

	FontInit();
	FlagInit();

	time_t t0, tprev = 0;
	struct timeval tv0, tv_prev, tv_diff;
	gettimeofday(&tv_prev, NULL);
	while (!mainloopend) {
		EventCheck();

		RenderFunc();

		++fps;
		t0 = time(NULL);
		if (t0 - tprev > 0) {
			tprev = t0;
			sprintf(fps_text, "%u fps", fps);
			fps = 0;
		}

		gettimeofday(&tv0, NULL);
		tvdiff(&tv_prev, &tv0, &tv_diff);
		if (tv_diff.tv_sec >= 1 || tv_diff.tv_usec >= 500000) {
			tv_prev.tv_sec = tv0.tv_sec;
			tv_prev.tv_usec = tv0.tv_usec;
			terminal_cursor_blink = !terminal_cursor_blink;
		}

		delta += 1.0;
		if (delta >= 360.0)
			delta -= 360.0;

		FlagUpdate();
	}

	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

