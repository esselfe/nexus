#include <GL/gl.h>

#include "element.h"
#include "image.h"

GLfloat shop_x = -50.0, shop_y = 0.0, shop_z = 50.0;
GLfloat shop_width = 20.0, shop_height = 4.0, shop_depth = 10.0;
GLuint shop_texture_id_planks_001, shop_texture_id_planks_002,
    shop_texture_id_planks_003, shop_texture_id_planks_004;
GLuint shop_display_list;

void ElementShopInit(void) {
    ElementTextureCreate(&shop_texture_id_planks_001, "images/planks-001-128.png");
    ElementTextureCreate(&shop_texture_id_planks_002, "images/planks-002-128.png");
    ElementTextureCreate(&shop_texture_id_planks_003, "images/planks-003-128.png");
    ElementTextureCreate(&shop_texture_id_planks_004, "images/planks-004-128.png");

    // Create the shop display list
    shop_display_list = glGenLists(1);
    glNewList(shop_display_list, GL_COMPILE);

    // Front
    glBindTexture(GL_TEXTURE_2D, shop_texture_id_planks_001);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-(shop_width/2.0), 0.0, -(shop_depth/2.0));
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-(shop_width/2.0) + 1.0, 0.0, -(shop_depth/2.0));
    glTexCoord2f(1.0, shop_height);
    glVertex3f(-(shop_width/2.0) + 1.0, shop_height, -(shop_depth/2.0));
    glTexCoord2f(0.0, shop_height);
    glVertex3f(-(shop_width/2.0), shop_height, -(shop_depth/2.0));
    glEnd();

    glBindTexture(GL_TEXTURE_2D, shop_texture_id_planks_002);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-(shop_width/2.0) + 1.0, shop_height - 1.0, -(shop_depth/2.0));
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-(shop_width/2.0) + 3.0, shop_height - 1.0, -(shop_depth/2.0));
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-(shop_width/2.0) + 3.0, shop_height, -(shop_depth/2.0));
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-(shop_width/2.0) + 1.0, shop_height, -(shop_depth/2.0));
    glEnd();

    glBindTexture(GL_TEXTURE_2D, shop_texture_id_planks_003);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
     glVertex3f(-(shop_width/2.0) + 3.0, 0.0, -(shop_depth/2.0));
    glTexCoord2f((shop_width - 3.0)/4.0, 0.0);
     glVertex3f(shop_width/2.0, 0.0, -(shop_depth/2.0));
    glTexCoord2f((shop_width - 3.0)/4.0, shop_height/2.0);
     glVertex3f(shop_width/2.0, shop_height, -(shop_depth/2.0));
    glTexCoord2f(0.0, shop_height/2.0);
     glVertex3f(-(shop_width/2.0) + 3.0, shop_height, -(shop_depth/2.0));
    glEnd();

    // Left side
    glBindTexture(GL_TEXTURE_2D, shop_texture_id_planks_004);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-(shop_width/2.0), 0.0, shop_depth/2.0);
    glTexCoord2f(shop_depth/2.0, 0.0);
    glVertex3f(-(shop_width/2.0), 0.0, -(shop_depth/2.0));
    glTexCoord2f(shop_depth/2.0, shop_height/2.0);
    glVertex3f(-(shop_width/2.0), shop_height, -(shop_depth/2.0));
    glTexCoord2f(0.0, shop_height/2.0);
    glVertex3f(-(shop_width/2.0), shop_height, shop_depth/2.0);
    glEnd();

    // Right side
    glBindTexture(GL_TEXTURE_2D, shop_texture_id_planks_002);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(shop_width/2.0, 0.0, shop_depth/2.0);
    glTexCoord2f(shop_depth/2.0, 0.0);
    glVertex3f(shop_width/2.0, 0.0, -(shop_depth/2.0));
    glTexCoord2f(shop_depth/2.0, shop_height/2.0);
    glVertex3f(shop_width/2.0, shop_height, -(shop_depth/2.0));
    glTexCoord2f(0.0, shop_height/2.0);
    glVertex3f(shop_width/2.0, shop_height, shop_depth/2.0);
    glEnd();

    // Back side
    glBindTexture(GL_TEXTURE_2D, shop_texture_id_planks_003);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-(shop_width/2.0), 0.0, shop_depth/2.0);
    glTexCoord2f(shop_width/4.0, 0.0);
    glVertex3f(shop_width/2.0, 0.0, shop_depth/2.0);
    glTexCoord2f(shop_width/4.0, shop_height/2.0);
    glVertex3f(shop_width/2.0, shop_height, shop_depth/2.0);
    glTexCoord2f(0.0, shop_height/2.0);
    glVertex3f(-(shop_width/2.0), shop_height, shop_depth/2.0);
    glEnd();

    // Top side
    glBindTexture(GL_TEXTURE_2D, shop_texture_id_planks_004);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-(shop_width/2.0), shop_height, -(shop_depth/2.0));
    glTexCoord2f(shop_width/4.0, 0.0);
    glVertex3f(shop_width/2.0, shop_height, -(shop_depth/2.0));
    glTexCoord2f(shop_width/4.0, shop_depth/2.0);
    glVertex3f(shop_width/2.0, shop_height, shop_depth/2.0);
    glTexCoord2f(0.0, shop_depth/2.0);
    glVertex3f(-(shop_width/2.0), shop_height, shop_depth/2.0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glEndList();
}

void ElementShopRender(void) {
    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);
    glTranslatef(shop_x, shop_y, shop_z);
    glColor4f(0.2, 0.25, 0.3, 1.0);

    glCallList(shop_display_list);

    glPopMatrix();
}
