#include <stdio.h>

#include "nexus.h"

unsigned int state;

unsigned int StateGet(void) {
	return state;
}

void StateSet(unsigned int state) {
	switch(state) {
	case STATE_MAIN:
		state = STATE_MAIN;
		RenderFunc = Render;
		break;
	case STATE_BROWSER:
		state = STATE_BROWSER;
		RenderFunc = Render;
		break;
	case STATE_EDITOR:
		state = STATE_EDITOR;
		RenderFunc = Render;
		break;
	case STATE_MEMORY:
		state = STATE_MEMORY;
		RenderFunc = Render;
		break;
	}
}

