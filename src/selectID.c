#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

#include "selectID.h"
/*
struct SelectID {
    struct SelectID *prev, *next;
    GLuint id;
};

struct SelectIDList {
    struct SelectID *first_id, *last_id;
    unsigned long long total_ids;
};*/
struct SelectIDList root_selectid_list;

void SelectIDInit(void) {
    root_selectid_list.first_id = NULL;
    root_selectid_list.last_id = NULL;
}

struct SelectID *SelectIDNew(void) {
    struct SelectID *sid = malloc(sizeof(struct SelectID));

    if (root_selectid_list.first_id == NULL) {
        root_selectid_list.first_id = sid;
        root_selectid_list.last_id = sid;
        root_selectid_list.total_ids = 1;

        sid->prev = NULL;
        sid->next = NULL;
        sid->id = 1;
    }
    else {
        root_selectid_list.last_id->next = sid;
        sid->prev = root_selectid_list.last_id;
        sid->next = NULL;
        sid->id = sid->prev->id + 1;
        root_selectid_list.last_id = sid;
    }

    return sid;
}

void SelectIDDelete(GLuint id) {
    return;
}