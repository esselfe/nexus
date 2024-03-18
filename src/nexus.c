#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <getopt.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "nexus.h"
#include "camera.h"
#include "delta.h"
#include "event.h"
#include "flag.h"
#include "floor.h"
#include "font.h"
#include "mode.h"
#include "moon.h"
#include "render.h"
#include "selectID.h"
#include "sky.h"
#include "modules/file-browser/file-browser.h"

char *nexus_version_string = "0.2.2-git";
int verbose;
int mainloopend; // The program should exit if set to 1
int init_done; // Internal use
SDL_DisplayMode display_mode;
SDL_Window *window;
SDL_GLContext context;
// Window position and dimensions
GLfloat winX = 100.0, winY = 40.0, winW = 800.0, winH = 600.0;
char window_title[1024];
unsigned int fps; // For measuring frames per second
char *fps_text; // Text rendered on the HUD
time_t t0, tprev; // Mostly used in delta code
struct timeval tv0, tv_prev, tv_diff; // Idem

// Structure of getopt options for program options and arguments processing
static const struct option long_options[] = {
	{"help", no_argument, NULL, 'h'},
	{"version", no_argument, NULL, 'V'},
	{"verbose", no_argument, NULL, 'v'},
	{"floor-factor", required_argument, NULL, 'f'},
	{"position-x", required_argument, NULL, 'X'},
	{"position-y", required_argument, NULL, 'Y'},
	{"width", required_argument, NULL, 'W'},
	{"height", required_argument, NULL, 'H'},
	{NULL, 0, NULL, 0}
};
static const char *short_options = "hVvf:X:Y:W:H:";

// This function will be called if exit(N); is called or at the end of main()
// It's set with the atexit() function in the main() function
void NexusExit(void) {
	// Prevent saving zeroes if exit() was called before
	// the score was loaded.
	if (init_done) {
		if (verbose) printf("Saving element score\n");
		ElementScoreSave();
	}
	
	if (verbose) printf("\nnexus exited\n");
}

// Calculate the difference between 2 timings like 0.223880 and 0.384859
void tvdiff(struct timeval *tv_start, struct timeval *tv_end, struct timeval *tv_diff2) {
	tv_diff2->tv_sec = tv_end->tv_sec - tv_start->tv_sec;
	
	if (tv_start->tv_sec == tv_end->tv_sec) {
		tv_diff2->tv_usec = tv_end->tv_usec - tv_start->tv_usec;
	}
	else {
		tv_diff2->tv_usec = tv_end->tv_usec + (1000000-tv_start->tv_usec);
		if (tv_diff2->tv_usec >= 1000000) {
			++tv_diff2->tv_sec;
			tv_diff2->tv_usec -= 1000000;
		}
		if (tv_diff2->tv_sec > 0)
			--tv_diff2->tv_sec;
	}
}

void ShowHelp(void) {
	printf("Options: -H/--help | -V/--version | -v/--verbose | -f/--floor-factor NUM |\n"
		"  -X/--position-x PIXELS | -Y/--position-y PIXELS |\n"
		"  -W/--width PIXELS | -H/--height PIXELS\n");
}

void ShowVersion(void) {
	printf("nexus %s\n", nexus_version_string);
}

// Program entry point
int main(int argc, char **argv) {
	// Process program arguments
	int c;
	while (1) {
		c = getopt_long(argc, argv, short_options, long_options, NULL);
		if (c == -1)
			break;
		
		switch (c) {
		case 'h': // --help
			ShowHelp();
			exit(0);
		case 'V': // --version
			ShowVersion();
			exit(0);
		case 'v': // --verbose
			verbose = 1;
			break;
		case 'f': // --floor-factor
			if (optarg != NULL)
				floor_factor = atoi(optarg);
			
			if (floor_factor <= 0)
				floor_factor = 1;
			break;
		case 'X': // --position-x
			if (optarg != NULL)
				winX = atoi(optarg);
			break;
		case 'Y': // --position-y
			if (optarg != NULL)
				winY = atoi(optarg);
			break;
		case 'W': // --width
			if (optarg != NULL)
				winW = atoi(optarg);
			break;
		case 'H': // --height
			if (optarg != NULL)
				winH = atoi(optarg);
			break;
		default:
			printf("nexus error: Unknown argument: %c (%d)\n", (char)c, c);
			break;
		}
	}
	
	if (verbose)
		printf("nexus %s started\n", nexus_version_string);
	
	atexit(NexusExit);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf ("nexus: SDL_Init() failed.\n");
		exit(1);
	}

	// Set OpenGL API version to 1.1 and show what we got
	int gl_major, gl_minor;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_minor);
	if (verbose) printf("Using OpenGL %d.%d\n", gl_major, gl_minor);

	sprintf(window_title, "nexus %s", nexus_version_string);
	window = SDL_CreateWindow(window_title, winX, winY, winW, winH,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		printf("nexus: Cannot create SDL2/GL context. Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	// Needs a context
	if (verbose) printf("OpenGL %s installed\n", glGetString(GL_VERSION));

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf ("nexus: Cannot initialize GLEW.\n");
		SDL_GL_DeleteContext(context);
		SDL_Quit();
		exit(1);
	}

	fps_text = malloc(20);
	sprintf(fps_text, "0 fps");

	ModeSet(MODE_MAIN);
	EventInit();
	DeltaInit();
	CameraInit();
	FontInit(); // There must be no display list creation before this call
	SelectIDInit();
	RenderInit();
	FloorInit();
	ElementInit();
	FlagInit();
	SkyInit();
	MoonInit();
	FileBrowserInit();
	EditorInit();
	MemoryInit();
	
	init_done = 1;

	tprev = time(NULL);
	gettimeofday(&tv_prev, NULL);
	if (verbose) printf("Mainloop started\n");
	while (!mainloopend) {
		++fps;
		EventFunc();
		DeltaFunc();
		if (cam.moving) CameraMove();
		if (goto_enabled) CameraGotoMove();
		if (render) RenderFunc();
	}

	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

