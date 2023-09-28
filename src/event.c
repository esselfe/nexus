#include <SDL2/SDL.h>

#include "nexus.h"

unsigned int mods;
unsigned int show_keys;
int mouse_x, mouse_y, mouse_x_prev, mouse_y_prev;
unsigned int mouse_button, mouse_held;
static SDL_Event event;

void (*EventFunc)(void);

void EventInit(void) {
	if (verbose) printf("Initializing events\n");
	mouse_x_prev = mouse_x = (int)winW/2;
	mouse_y_prev = mouse_y = (int)winH/2;
	SDL_WarpMouseInWindow(window, mouse_x, mouse_y);
	SDL_ShowCursor(0);
}

char ShiftKey(SDL_Keycode key) {
	switch (key) {
	case SDLK_BACKQUOTE:
		return '~';
	case SDLK_1:
		return '!';
	case SDLK_2:
		return '@';
	case SDLK_3:
		return '#';
	case SDLK_4:
		return '$';
	case SDLK_5:
		return '%';
	case SDLK_6:
		return '^';
	case SDLK_7:
		return '&';
	case SDLK_8:
		return '*';
	case SDLK_9:
		return '(';
	case SDLK_0:
		return ')';
	case SDLK_MINUS:
		return '_';
	case SDLK_EQUALS:
		return '+';
	case SDLK_LEFTBRACKET:
		return '{';
	case SDLK_RIGHTBRACKET:
		return '}';
	case SDLK_BACKSLASH:
		return '|';
	case SDLK_SEMICOLON:
		return ':';
	case SDLK_QUOTE:
		return '"';
	case SDLK_COMMA:
		return '<';
	case SDLK_PERIOD:
		return '>';
	case SDLK_SLASH:
		return '?';
	}
	
	if (key >= 'a' && key <= 'z')
		return (char)key-32;
	
	return 32;
}

void EventCheck(void) {
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			mainloopend = 1;
		else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			if (show_keys)
				printf("key: %s\n", SDL_GetKeyName(event.key.keysym.sym));

			if (terminal_visible && (event.key.keysym.sym >= SDLK_SPACE && 
				event.key.keysym.sym <= SDLK_z)) {
				if (mods & MOD_CTRL && event.key.keysym.sym == SDLK_c) {
					terminal_cursor_pos = 0;
					memset(terminal_buffer, 0, TERMINAL_BUFFER_SIZE);
				}
				else if (terminal_cursor_pos < TERMINAL_BUFFER_SIZE) {
					if (mods & MOD_SHIFT)
						terminal_buffer[terminal_cursor_pos++] = ShiftKey(event.key.keysym.sym);
					else
						terminal_buffer[terminal_cursor_pos++] = event.key.keysym.sym;
				}	
				return;
			}
			else if (terminal_visible && event.key.keysym.sym == SDLK_BACKSPACE) {
				if (terminal_cursor_pos > 0)
					terminal_buffer[--terminal_cursor_pos] = '\0';
				return;
			}
			else if (terminal_visible && event.key.keysym.sym == SDLK_RETURN) {
				TerminalParse();
				return;
			}
			
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				mainloopend = 1;
				break;
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				mods |= MOD_CTRL;
				break;
			case SDLK_LALT:
			case SDLK_RALT:
				mods |= MOD_ALT;
				break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				mods |= MOD_SHIFT;
				break;
			case SDLK_TAB:
				terminal_visible = !terminal_visible;
				break;
			case SDLK_UP:
				if (cam.moving & MOVE_DECEL)
					cam.moving ^= MOVE_DECEL;
				
				cam.moving |= MOVE_ACCEL;
				cam.moving |= MOVE_FRONT;
				if (cam.moving & MOVE_BACK)
					cam.moving ^= MOVE_BACK;
				if (goto_enabled)
					goto_enabled = 0;
				if (goto_stopping)
					goto_stopping = 0;
				break;
			case SDLK_DOWN:
				if (cam.moving & MOVE_DECEL)
					cam.moving ^= MOVE_DECEL;
				
				cam.moving |= MOVE_ACCEL;
				cam.moving |= MOVE_BACK;
				if (cam.moving & MOVE_FRONT)
					cam.moving ^= MOVE_FRONT;
				if (goto_enabled)
					goto_enabled = 0;
				if (goto_stopping)
					goto_stopping = 0;
				break;
			case SDLK_LEFT:
				if (cam.moving & MOVE_SIDE_DECEL)
					cam.moving ^= MOVE_SIDE_DECEL;
				cam.moving |= MOVE_SIDE_ACCEL;
				cam.moving |= MOVE_LEFT;
				if (cam.moving & MOVE_RIGHT)
					cam.moving ^= MOVE_RIGHT;
				if (goto_enabled)
					goto_enabled = 0;
				if (goto_stopping)
					goto_stopping = 0;
				break;
			case SDLK_RIGHT:
				if (cam.moving & MOVE_SIDE_DECEL)
					cam.moving ^= MOVE_SIDE_DECEL;
				cam.moving |= MOVE_SIDE_ACCEL;
				cam.moving |= MOVE_RIGHT;
				if (cam.moving & MOVE_LEFT)
					cam.moving ^= MOVE_LEFT;
				if (goto_enabled)
					goto_enabled = 0;
				if (goto_stopping)
					goto_stopping = 0;
				break;
			case SDLK_PAGEUP:
				if (cam.moving & MOVE_HEIGHT_DECEL)
					cam.moving ^= MOVE_HEIGHT_DECEL;
				cam.moving |= MOVE_HEIGHT_ACCEL;
				cam.moving |= MOVE_UP;
				if (cam.moving & MOVE_DOWN)
					cam.moving ^= MOVE_DOWN;
				break;
			case SDLK_PAGEDOWN:
				if (cam.moving & MOVE_HEIGHT_DECEL)
					cam.moving ^= MOVE_HEIGHT_DECEL;
				cam.moving |= MOVE_HEIGHT_ACCEL;
				cam.moving |= MOVE_DOWN;
				if (cam.moving & MOVE_UP)
					cam.moving ^= MOVE_UP;
				break;
			case SDLK_KP_4:
				cam.moving |= LOOK_LEFT;
				if (goto_enabled)
					goto_enabled = 0;
				if (goto_stopping)
					goto_stopping = 0;
				break;
			case SDLK_KP_6:
				cam.moving |= LOOK_RIGHT;
				if (goto_enabled)
					goto_enabled = 0;
				if (goto_stopping)
					goto_stopping = 0;
				break;
			case SDLK_KP_7:
				light_position[0] -= 10.0;
				glLightfv(GL_LIGHT0, GL_POSITION, light_position);
				break;
			case SDLK_KP_9:
				light_position[0] += 10.0;
				glLightfv(GL_LIGHT0, GL_POSITION, light_position);
				break;
			case SDLK_KP_MINUS:
				if (!(cam.moving & THR_DOWN))
					cam.moving ^= THR_DOWN;
				break;
			case SDLK_KP_PLUS:
				if (!(cam.moving & THR_UP))
					cam.moving ^= THR_UP;
				break;
			case SDLK_F1:
				ModeSet(MODE_MAIN);
				break;
			case SDLK_b:
				if (ModeGet() != MODE_BROWSER)
					ModeSet(MODE_BROWSER);
				else
					ModeSet(mode_prev);
				break;
			case SDLK_d:
				ModeSet(MODE_DRIVING);
				break;
			case SDLK_e:
				if (mods & MOD_SHIFT) {
					if (ModeGet() != MODE_ELEMENT)
						ModeSet(MODE_ELEMENT);
					else
						ModeSet(mode_prev);
				}
				else {
					if (ModeGet() != MODE_EDITOR)
						ModeSet(MODE_EDITOR);
					else
						ModeSet(mode_prev);
				}
				break;
			case SDLK_k:
				show_keys = !show_keys;
				break;
			case SDLK_m:
				if (ModeGet() != MODE_MEMORY)
					ModeSet(MODE_MEMORY);
				else
					ModeSet(mode_prev);
				break;
			case SDLK_p:
				printf("position: x: %f y: %f z: %f lx: %f ly: %f lz: %f angle: %f\n",
					cam.x, cam.y, cam.z, cam.lx, cam.ly, cam.lz, cam.rotation_angle);
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				mods ^= MOD_CTRL;
				break;
			case SDLK_LALT:
			case SDLK_RALT:
				mods ^= MOD_ALT;
				break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				mods ^= MOD_SHIFT;
				break;
			case SDLK_UP:
			case SDLK_DOWN:
			  	cam.moving |= MOVE_DECEL;
	  			if (cam.moving & MOVE_ACCEL)
				  	cam.moving ^= MOVE_ACCEL;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				cam.moving |= MOVE_SIDE_DECEL;
				if (cam.moving & MOVE_SIDE_ACCEL)
					cam.moving ^= MOVE_SIDE_ACCEL;
				break;
			case SDLK_PAGEUP:
			case SDLK_PAGEDOWN:
			  	cam.moving |= MOVE_HEIGHT_DECEL;
	  			if (cam.moving & MOVE_HEIGHT_ACCEL)
				  	cam.moving ^= MOVE_HEIGHT_ACCEL;
				break;
			case SDLK_KP_4:
				cam.moving ^= LOOK_LEFT;
				break;
			case SDLK_KP_6:
				cam.moving ^= LOOK_RIGHT;
				break;
			case SDLK_KP_MINUS:
				if (cam.moving & THR_DOWN)
					cam.moving ^= THR_DOWN;
				break;
			case SDLK_KP_PLUS:
				if (cam.moving & THR_UP)
					cam.moving ^= THR_UP;
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_RIGHT)
				mouse_held = !mouse_held;

			if (mouse_held) {
				mouse_x_prev = mouse_x = (int)winW/2;
				mouse_y_prev = mouse_y = (int)winH/2;
				SDL_WarpMouseInWindow(window, mouse_x, mouse_y);
			}
		}
		else if (event.type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&mouse_x, &mouse_y);

			if (mouse_held) {
				if (mouse_x - mouse_x_prev > 0)
					CameraRotateStep(0.0005 * (mouse_x - mouse_x_prev) * delta_move);
				else if (mouse_x - mouse_x_prev < 0)
					CameraRotateStep(-0.0005 * (mouse_x_prev - mouse_x) * delta_move);

				mouse_x_prev = mouse_x;
				mouse_y_prev = mouse_y;
				if (mouse_x < 50 || mouse_x > winW-50 ||
					mouse_y < 50 || mouse_y > winH-50) {
					mouse_x_prev = mouse_x = (int)winW/2;
					mouse_y_prev = mouse_y = (int)winH/2;
					SDL_WarpMouseInWindow(window, mouse_x, mouse_y);
				}
			}
			else {
				mouse_x_prev = mouse_x;
				mouse_y_prev = mouse_y;
			}
		}
	}
}

