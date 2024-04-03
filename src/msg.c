#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

#include "font.h"
#include "window.h"
#include "msg.h"

struct MessageBoard message_board;

void MsgInit(void) {
    message_board.first_message = NULL;
    message_board.last_message = NULL;
    message_board.current_message = NULL;
    message_board.x = 100.0;
    message_board.y = winH - 10.0;
    message_board.width = 600.0;
    message_board.height = 200.0;
    message_board.alpha = 0.85;
    message_board.visible = 0;
    message_board.total_messages = 0;

    MsgAdd("Message 1");
    MsgAdd("Message 2");
    MsgAdd("Message 3");
}
/*struct Message {
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
};*/
void MsgAdd(char *text) {
    struct Message *msg = malloc(sizeof(struct Message));

    if (message_board.total_messages == 0) {
        message_board.first_message = msg;
        msg->prev = NULL;
        msg->next = NULL;
        msg->x = message_board.x;
        msg->y = message_board.y - message_board.height;
    }
    else {
        message_board.last_message->next = msg;
        msg->prev = message_board.last_message;
        msg->next = NULL;
        msg->y = msg->prev->y + 20.0;
    }
    msg->x = message_board.x;
    msg->total_lines = (strlen(text) * 8) / (message_board.width / 8);
    msg->length = strlen(text);
    snprintf(msg->text, 1023, "%s", text);

    message_board.last_message = msg;
    message_board.current_message = msg;
    ++message_board.total_messages;
}

void MsgHide(void) {
    message_board.visible = 0;
}

void MsgPopFirst(void);

void MsgRender(void) {
    struct MessageBoard *mb = &message_board;

    glEnable(GL_BLEND);
    glPushMatrix();
    glColor4f(0.1, 0.15, 0.2, message_board.alpha);
    glTranslatef(mb->x, mb->y, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, -mb->height);
    glVertex2f(mb->width, -mb->height);
    glVertex2f(mb->width, 0.0);
    glEnd();
    glPopMatrix();

    struct Message *msg = message_board.first_message;
    while (msg != NULL) {
        FontRender2D(BG_NONE, msg->x, msg->y, msg->text);
        msg = msg->next;
    }
}

void MsgShow(void) {
    message_board.visible = 1;
}
