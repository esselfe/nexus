#ifndef EVENT_H
#define EVENT_H 1

#define MOD_NONE    0
#define MOD_CTRL    1
#define MOD_ALT     (1<<1)
#define MOD_SHIFT   (1<<2)

extern unsigned int mods; // Each bit can be set to one of the flags above
extern unsigned int show_keys; // Show keys pressed on the standard output stream
extern int mouse_x, mouse_y, mouse_x_prev, mouse_y_prev;
extern unsigned int mouse_held; // Mouse moves camera rotation or cursor

void EventCheck(void);
// Modules are supposed to associate this handler to their function
extern void (*EventFunc)(void);
void EventInit(void);

#endif /* EVENT_H */