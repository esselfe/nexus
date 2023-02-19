#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <GL/gl.h>

#include "nexus.h"

unsigned int terminal_visible;
char terminal_buffer[TERMINAL_BUFFER_SIZE];
unsigned int terminal_cursor_pos, terminal_cursor_blink;

void TerminalParse(void) {
	char w1[128], w2[128], w3[128], w4[128];
	memset(w1, 0, 128);
	memset(w2, 0, 128);
	memset(w3, 0, 128);
	memset(w4, 0, 128);
	unsigned int current_word = 0, wcnt = 0, bcnt = 0;
	char *c = terminal_buffer;
	while (1) {
		if (current_word == 0) {
			if (*c != ' ')
				w1[wcnt++] = terminal_buffer[bcnt++];
			else {
				++current_word;
				wcnt = 0;
				++bcnt;
			}
			if (bcnt >= TERMINAL_BUFFER_SIZE)
				break;
			else if (wcnt >= 128)
				break;
		}
		else if (current_word == 1) {
			if (*c != ' ')
				w2[wcnt++] = terminal_buffer[bcnt++];
			else {
				++current_word;
				wcnt = 0;
				++bcnt;
			}
			if (bcnt >= TERMINAL_BUFFER_SIZE)
				break;
			else if (wcnt >= 128)
				break;
		}
		else if (current_word == 2) {
			if (*c != ' ')
				w3[wcnt++] = terminal_buffer[bcnt++];
			else {
				++current_word;
				wcnt = 0;
				++bcnt;
			}
			if (bcnt >= TERMINAL_BUFFER_SIZE)
				break;
			else if (wcnt >= 128)
				break;
		}
		else if (current_word == 3) {
			if (*c != ' ')
				w4[wcnt++] = terminal_buffer[bcnt++];
			else
				break;
			
			
			if (bcnt >= TERMINAL_BUFFER_SIZE)
				break;
			else if (wcnt >= 128)
				break;
		}

		++c;
		if (*c == '\0')
			break;
	}

	if (strlen(w1)) {
		if (strcmp(w1, "exit") == 0 || strcmp(w1, "quit") == 0 ||
			strcmp(w1, "qw") == 0)
			mainloopend = 1;
		else if (strcmp(w1, "browser") == 0)
			StateSet(STATE_BROWSER);
		else if (strcmp(w1, "editor") == 0)
			StateSet(STATE_EDITOR);
		else if (strcmp(w1, "element") == 0 && !strlen(w2))
			StateSet(STATE_ELEMENT);
		else if (strcmp(w1, "element") == 0 && strlen(w2)) {
			if (strcmp(w2, "add") == 0)
				ElementAdd(atoi(w3));
		}
		else if (strcmp(w1, "goto") == 0 && strlen(w2) && strlen(w3))
			CameraGoto(atof(w2), atof(w3));
		else if (strcmp(w1, "jump") == 0 && strlen(w2) && strlen(w3))
			CameraJump(atof(w2), atof(w3));
		else if (strcmp(w1, "main") == 0)
			StateSet(STATE_MAIN);
		else if (strcmp(w1, "memory") == 0)
			StateSet(STATE_MEMORY);
	}

	terminal_cursor_pos = 0;
	memset(terminal_buffer, 0, TERMINAL_BUFFER_SIZE);
}

void TerminalRender(void) {
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
	glVertex3i(10, 10, 0);
	glVertex3i(10, 34, 0);
	glVertex3i((int)winW-10, 34, 0);
	glVertex3i((int)winW-10, 10, 0);
	glEnd();

	if (terminal_cursor_blink) {
		glColor3f(0.1, 0.1, 0.1);
		glBegin(GL_LINES);
		glVertex3i(terminal_cursor_pos * 8 + 12, 12, 1);
		glVertex3i(terminal_cursor_pos * 8 + 12, 32, 1);
		glEnd();
	}

	if (strlen(terminal_buffer))
		FontRender2D(BG_BLACK, 12, 14, terminal_buffer);
}

