#ifndef ELEMENT_H
#define ELEMENT_H 1

#include <GL/gl.h>

#define ELEMENT_TYPE_WASTE   0
#define ELEMENT_TYPE_BATTERY 1
#define ELEMENT_TYPE_COPPER  2
#define ELEMENT_TYPE_GOLD    3
#define ELEMENT_TYPE_IRON    4
#define ELEMENT_TYPE_MAGNET  5
#define ELEMENT_TYPE_ROCK    6
#define ELEMENT_TYPE_RUBBER  7
#define ELEMENT_TYPE_SILVER  8
#define ELEMENT_TYPE_WOOD    9

struct Element {
	struct Element *prev, *next;
	unsigned int type;
	float x, y, z;
	float width, height;
	float angle_x, angle_y, angle_z;
	GLuint texture_id;
	unsigned int value;
};
struct ElementList {
	struct Element *first_element, *last_element;
	unsigned int total_elements;
};

extern struct ElementList element_root_list;
extern unsigned long long total_waste, total_battery, total_copper, total_gold,
	total_iron, total_magnet, total_rock, total_rubber, total_silver, total_wood;
extern char total_waste_text[128], total_battery_text[128],
	total_copper_text[128], total_gold_text[128], total_iron_text[128],
	total_magnet_text[128], total_rock_text[128], total_rubber_text[128],
	total_silver_text[128], total_wood_text[128];
extern GLuint texture_id_waste, texture_id_battery, texture_id_copper,
	texture_id_gold, texture_id_iron, texture_id_magnet, texture_id_rock,
	texture_id_rubber, texture_id_silver, texture_id_wood;
extern GLfloat element_mat_amb_diff[4];
extern struct timeval tv_score_saved;
extern unsigned long long element_credits;

void ElementAdd(unsigned int count);
void ElementCleanArea(void);
void ElementCreditLoad(void);
void ElementCreditSave(void);
void ElementDelta(void);
void ElementInit(void);
void ElementListDestroy(void);
void ElementRemove(struct Element *elem);
void ElementRender(void);
void ElementScoreLoad(void);
void ElementScoreSave(void);
void ElementShopInit(void);
void ElementShopCheckCollision(void);
void ElementShopRender(void);
void ElementTextureInit(void);
void ElementTextureCreate(GLuint *id, char *filename);
void ElementThreadStart(void);

#endif /* ELEMENT_H */