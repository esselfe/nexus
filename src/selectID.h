#ifndef SELECTID_H
#define SELECTID_H 1

#include <GL/gl.h>

struct SelectID {
    struct SelectID *prev, *next;
    GLuint id;
};

struct SelectIDList {
    struct SelectID *first_id, *last_id;
    unsigned long long total_ids;
};
extern struct SelectIDList root_selectid_list;

void SelectIDInit(void);
struct SelectID *SelectIDNew(void);
void SelectIDDelete(GLuint id);

#endif /* SELECTID_H */