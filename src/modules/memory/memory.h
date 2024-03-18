#ifndef MEMORY_H
#define MEMORY_H 1

#include <GL/gl.h>

extern GLfloat memory_max, memory_value;
extern char memory_max_text[128], memory_value_text[128];
extern GLfloat swap_max, swap_value;
extern char swap_max_text[128], swap_value_text[128];
extern GLfloat memory_mat_amb_diff[4];

void MemoryDeltaCompute(void);
void MemoryInit(void);
void MemoryRender(void);

#endif /* MEMORY_H */