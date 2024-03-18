#include <GL/gl.h>

extern GLfloat delta, delta_move;

void DeltaCompute(void);
void DeltaInit(void);
// Modules are supposed to associate this handler to their function
extern void (*DeltaFunc)(void);
void DeltaMove(void);
