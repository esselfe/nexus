#ifndef TERMINAL_H
#define TERMINAL_H 1

#define TERMINAL_BUFFER_SIZE 4096

// Enables or disables the terminal
extern unsigned int terminal_visible;
extern char terminal_buffer[TERMINAL_BUFFER_SIZE];
extern unsigned int terminal_cursor_pos;
// Toggled once every half second in delta.c
extern unsigned int terminal_cursor_blink;

void TerminalParse(void);
void TerminalRender(void);

#endif /* TERMINAL_H */