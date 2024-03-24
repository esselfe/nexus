#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "nexus.h"
#include "args.h"
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
#include "window.h"
#include "modules/editor/editor.h"
#include "modules/element/element.h"
#include "modules/file-browser/file-browser.h"
#include "modules/memory/memory.h"

char *nexus_version_string = "0.2.4-git";
int verbose;
int mainloopend; // The program should exit if set to 1
int init_done; // Internal use

// This function will be called if exit(N); is called or at the end of main()
// It's set with the atexit() function in the main() function
static void NexusExit(void) {
	// Prevent saving zeroes if exit() was called before
	// the score was loaded.
	if (init_done) {
		if (verbose) printf("Saving element credits and score\n");
		ElementCreditSave();
		ElementScoreSave();
	}
	
	if (verbose) printf("\nnexus exited\n");
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
	ArgsParse(&argc, argv);
	
	if (verbose)
		printf("nexus %s started\n", nexus_version_string);
	
	atexit(NexusExit);

	WindowInit();

	// Needs a context from the window creation
	if (verbose) printf("OpenGL %s installed\n", glGetString(GL_VERSION));

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf ("nexus: Cannot initialize GLEW.\n");
		SDL_GL_DeleteContext(context);
		SDL_Quit();
		exit(1);
	}

	ModeSet(MODE_MAIN);
	EventInit();
	DeltaInit();
	CameraInit();
	FontInit(); // There must be no display list creation before this call
	SelectIDInit();
	RenderInit();
	FloorInit();
	FlagInit();
	SkyInit();
	MoonInit();
	ElementInit();
	FileBrowserInit();
	EditorInit();
	MemoryInit();
	
	init_done = 1;

	if (verbose) printf("Mainloop started\n");
	while (!mainloopend) {
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

