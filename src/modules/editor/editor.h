#ifndef EDITOR_H
#define EDITOR_H 1

struct LineNode {
	struct LineNode *prev, *next;
	unsigned long long line_number;
	unsigned long long length;
	char *text;
};
struct LineList {
	struct LineNode *first_line, *last_line;
	unsigned long long total_lines;
};
extern struct LineList line_root_list;

void EditorInit(void);
void EditorLoadFile(char *filename);
void EditorLineAdd(char *text);
void EditorLineRemove(unsigned long long line_number);
void EditorRender(void);

#endif /* EDITOR_H */