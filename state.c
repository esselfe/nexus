#include <stdio.h>

#include "nexus.h"

unsigned int state, state_prev;

unsigned int StateGet(void) {
	return state;
}

void StateSet(unsigned int newstate) {
	state_prev = state;
	switch(newstate) {
	case STATE_MAIN:
		state = STATE_MAIN;
		RenderFunc = Render;
		break;
	case STATE_BROWSER:
		state = STATE_BROWSER;
		RenderFunc = BrowserRender;
		break;
	case STATE_EDITOR:
		state = STATE_EDITOR;
		RenderFunc = EditorRender;
		break;
	case STATE_MEMORY:
		state = STATE_MEMORY;
		RenderFunc = MemoryRender;
		break;
	}
}

