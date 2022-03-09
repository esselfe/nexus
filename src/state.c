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
		EventFunc = EventCheck;
		RenderFunc = Render;
		break;
	case STATE_BROWSER:
		state = STATE_BROWSER;
		DeltaFunc = DeltaCompute;
		EventFunc = EventCheck;
		// EventFunc = BrowserEventCheck; // todo
		RenderFunc = BrowserRender;
		break;
/*	case STATE_DRIVING:
			state = STATE_DRIVING;
			DeltaFunc = DrivingDelta;
			EventFunc = DrivingEvent;
			RenderFunc = DrivingRender;
			break;
*/	case STATE_EDITOR:
		state = STATE_EDITOR;
		DeltaFunc = DeltaCompute;
		EventFunc = EventCheck;
		// EventFunc = EditorEventCheck; // todo
		RenderFunc = EditorRender;
		break;
	case STATE_MEMORY:
		state = STATE_MEMORY;
		DeltaFunc = MemoryDeltaCompute;
		EventFunc = EventCheck;
		// EventFunc = MemoryEventCheck; // todo
		RenderFunc = MemoryRender;
		break;
	}
}

