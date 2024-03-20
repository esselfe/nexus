#include <GL/gl.h>

#include "element.h"

GLfloat shop_x = -50.0, shop_y = 0.0, shop_z = 50.0;
GLfloat shop_width = 20.0, shop_height = 4.0, shop_depth = 10.0;

void ElementShopRender(void) {
    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);
    glTranslatef(shop_x, shop_y, shop_z);

    // Front
    glBegin(GL_POLYGON);
    glColor4f(0.2, 0.25, 0.3, 0.8);
    glVertex3f(-(shop_width/2.0), 0.0, -(shop_depth/2.0));
    glVertex3f(-(shop_width/2.0) + 1.0, 0.0, -(shop_depth/2.0));
    glVertex3f(-(shop_width/2.0) + 1.0, shop_height, -(shop_depth/2.0));
    glVertex3f(-(shop_width/2.0), shop_height, -(shop_depth/2.0));
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.2, 0.25, 0.3, 0.8);
    glVertex3f(-(shop_width/2.0) + 1.0, shop_height - 1.0, -(shop_depth/2.0));
    glVertex3f(-(shop_width/2.0) + 3.0, shop_height - 1.0, -(shop_depth/2.0));
    glVertex3f(-(shop_width/2.0) + 3.0, shop_height, -(shop_depth/2.0));
    glVertex3f(-(shop_width/2.0) + 1.0, shop_height, -(shop_depth/2.0));
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.2, 0.25, 0.3, 0.8);
    glVertex3f(-(shop_width/2.0) + 3.0, 0.0, -(shop_depth/2.0));
    glVertex3f(shop_width/2.0, 0.0, -(shop_depth/2.0));
    glVertex3f(shop_width/2.0, shop_height, -(shop_depth/2.0));
    glVertex3f(-(shop_width/2.0) + 3.0, shop_height, -(shop_depth/2.0));
    glEnd();

    // Left side
    glBegin(GL_POLYGON);
    glColor4f(0.2, 0.25, 0.3, 0.8);
    glVertex3f(-(shop_width/2.0), 0.0, shop_depth/2.0);
    glVertex3f(-(shop_width/2.0), 0.0, -(shop_depth/2.0));
    glVertex3f(-(shop_width/2.0), shop_height, -(shop_depth/2.0));
    glVertex3f(-(shop_width/2.0), shop_height, shop_depth/2.0);
    glEnd();

    // Right side
    glBegin(GL_POLYGON);
    glColor4f(0.2, 0.25, 0.3, 0.8);
    glVertex3f(shop_width/2.0, 0.0, shop_depth/2.0);
    glVertex3f(shop_width/2.0, 0.0, -(shop_depth/2.0));
    glVertex3f(shop_width/2.0, shop_height, -(shop_depth/2.0));
    glVertex3f(shop_width/2.0, shop_height, shop_depth/2.0);
    glEnd();

    // Back side
    glBegin(GL_POLYGON);
    glColor4f(0.2, 0.25, 0.3, 0.8);
    glVertex3f(-(shop_width/2.0), 0.0, shop_depth/2.0);
    glVertex3f(shop_width/2.0, 0.0, shop_depth/2.0);
    glVertex3f(shop_width/2.0, shop_height, shop_depth/2.0);
    glVertex3f(-(shop_width/2.0), shop_height, shop_depth/2.0);
    glEnd();

    glPopMatrix();
}