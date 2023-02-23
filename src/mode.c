#include <stdio.h>

#include "nexus.h"

unsigned int mode, mode_prev;

unsigned int ModeGet(void) {
	return mode;
}

void ModeSet(unsigned int newmode) {
	mode_prev = mode;
	switch(newmode) {
	case MODE_MAIN:
		mode = MODE_MAIN;
		DeltaFunc = DeltaCompute;
		EventFunc = EventCheck;
		RenderFunc = Render;
		break;
	case MODE_BROWSER:
		mode = MODE_BROWSER;
		DeltaFunc = DeltaCompute;
		EventFunc = EventCheck;
		// EventFunc = BrowserEventCheck; // todo
		RenderFunc = BrowserRender;
		break;
	case MODE_EDITOR:
		mode = MODE_EDITOR;
		DeltaFunc = DeltaCompute;
		EventFunc = EventCheck;
		// EventFunc = EditorEventCheck; // todo
		RenderFunc = EditorRender;
		break;
	case MODE_ELEMENT:
		mode = MODE_ELEMENT;
		DeltaFunc = ElementDelta;
		RenderFunc = ElementRender;
		break;
	case MODE_MEMORY:
		mode = MODE_MEMORY;
		DeltaFunc = MemoryDeltaCompute;
		EventFunc = EventCheck;
		// EventFunc = MemoryEventCheck; // todo
		RenderFunc = MemoryRender;
		break;
	}
}

