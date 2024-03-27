#include <stdio.h>
#include <string.h>
#include <GL/gl.h>

#include "camera.h"
#include "image.h"
#include "element.h"

GLfloat shop_x = -50.0, shop_y = 0.0, shop_z = 50.0;
GLfloat shop_width = 20.0, shop_height = 4.0, shop_depth = 10.0;
GLuint shop_texture_id_planks_001, shop_texture_id_planks_002,
    shop_texture_id_planks_003, shop_texture_id_planks_004;
GLuint shop_display_list;
unsigned int shop_is_near_camera;
unsigned int shop_convert_after_goto;
char *shop_convert_element_after_goto;

void ElementShopInit(void) {
    ElementTextureCreate(&shop_texture_id_planks_001, "images/planks-001-128.png");
    ElementTextureCreate(&shop_texture_id_planks_002, "images/planks-002-128.png");
    ElementTextureCreate(&shop_texture_id_planks_003, "images/planks-003-128.png");
    ElementTextureCreate(&shop_texture_id_planks_004, "images/planks-004-128.png");

    // Create the shop display list
    shop_display_list = glGenLists(1);
    glNewList(shop_display_list, GL_COMPILE);

    // Front
    // Left door side
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

    // Above door
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

    // Wall at the right of the door
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

unsigned int cooldown_time = 120, cooldown_cnt;
void ElementShopCheckCollision(void) {
    if (cam.x > shop_x - shop_width/2.0 - 1.5 &&
			cam.x < shop_x + shop_width/2.0 + 1.5 &&
			cam.z > shop_z - shop_depth/2.0 - 1.5 &&
			cam.z < shop_z + shop_depth/2.0 + 1.5) {
        if (!cooldown_cnt) {
            ++cooldown_cnt;
            CameraReverse();
        }
        else {
            ++cooldown_cnt;
            if (cooldown_cnt >= cooldown_time)
                cooldown_cnt = 0;
        }
    }
    else if (cooldown_cnt) cooldown_cnt = 0;

    // Check to see if camera is near
    if (cam.x > shop_x - shop_width/2.0 - 10.0 &&
			cam.x < shop_x + shop_width/2.0 + 10.0 &&
			cam.z > shop_z - shop_depth/2.0 - 10.0 &&
			cam.z < shop_z + shop_depth/2.0 + 10.0) {
        if (!shop_is_near_camera)
            shop_is_near_camera = 1;
        
        if (shop_convert_after_goto) {
            shop_convert_after_goto = 0;
            ElementShopConvert(shop_convert_element_after_goto);
        }
    }
    else {
        if (shop_is_near_camera)
            shop_is_near_camera = 0;
    }
}

void ElementShopConvert(char *type) {
    if (type == NULL) {
        ElementShopConvert("waste");
        ElementShopConvert("battery");
        ElementShopConvert("copper");
        ElementShopConvert("gold");
        ElementShopConvert("iron");
        ElementShopConvert("magnet");
        ElementShopConvert("rock");
        ElementShopConvert("rubber");
        ElementShopConvert("silver");
        ElementShopConvert("wood");
        return;
    }

    if (strcmp(type, "waste") == 0) {
        element_credits += total_waste/1000;
        total_waste = 0;
    }
    else if (strcmp(type, "battery") == 0) {
        element_credits += total_battery * 1000;
        total_battery = 0;
    }
    else if (strcmp(type, "copper") == 0) {
        element_credits += total_copper * 250;
        total_copper = 0;
    }
    else if (strcmp(type, "gold") == 0) {
        element_credits += total_gold * 5000;
        total_gold = 0;
    }
    else if (strcmp(type, "iron") == 0) {
        element_credits += total_iron * 250;
        total_iron = 0;
    }
    else if (strcmp(type, "magnet") == 0) {
        element_credits += total_magnet * 100;
        total_magnet = 0;
    }
    else if (strcmp(type, "rock") == 0) {
        element_credits += total_rock;
        total_rock = 0;
    }
    else if (strcmp(type, "rubber") == 0) {
        element_credits += total_rubber * 10;
        total_rubber = 0;
    }
    else if (strcmp(type, "silver") == 0) {
        element_credits += total_silver * 500;
        total_silver = 0;
    }
    else if (strcmp(type, "wood") == 0) {
        element_credits += total_wood * 10;
        total_wood = 0;
    }
}

void ElementShopRender(void) {
    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);
    glTranslatef(shop_x, shop_y, shop_z);
    glColor4f(0.2, 0.25, 0.3, 1.0);

    glCallList(shop_display_list);

    glPopMatrix();
}
