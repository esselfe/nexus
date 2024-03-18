#ifndef MODE_H
#define MODE_H 1

#define MODE_MAIN         0
#define MODE_FILE_BROWSER 1
#define MODE_DRIVING      2
#define MODE_EDITOR       3
#define MODE_ELEMENT      4
#define MODE_MEMORY       5

extern unsigned int mode, mode_prev;

unsigned int ModeGet(void);
void ModeSet(unsigned int newmode);

#endif /* MODE_H */