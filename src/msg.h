#ifndef MSG_H
#define MSG_H 1

#include <GL/gl.h>

struct Message {
    struct Message *prev, *next;
    unsigned long total_lines;
    GLfloat x, y;
    unsigned long length;
    char text[1024];
};
struct MessageBoard {
    struct Message *first_message, *last_message, *current_message;
    GLfloat x, y, width, height, alpha;
    unsigned int visible; // Boolean flag
    unsigned long total_messages;
};
extern struct MessageBoard message_board;

void MsgInit(void);
void MsgAdd(char *text);
void MsgHide(void);
void MsgPopFirst(void);
void MsgRender(void);
void MsgShow(void);

#endif /* MSG_H */