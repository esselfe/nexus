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
		DeltaFunc = DeltaCompute;
		RenderFunc = Render;
		break;
	case STATE_BROWSER:
		state = STATE_BROWSER;
		DeltaFunc = DeltaCompute;
		RenderFunc = BrowserRender;
		break;
	case STATE_EDITOR:
		state = STATE_EDITOR;
		DeltaFunc = DeltaCompute;
		RenderFunc = EditorRender;
		break;
	case STATE_MEMORY:
		state = STATE_MEMORY;
		DeltaFunc = MemoryDeltaCompute;
		RenderFunc = MemoryRender;
		break;
	}
}

