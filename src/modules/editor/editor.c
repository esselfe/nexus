#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "nexus.h"

struct LineList line_root_list;

void EditorInit(void) {
	line_root_list.first_line = NULL;
	line_root_list.last_line = NULL;
	line_root_list.total_lines = 0;
}

void EditorLoadFile(char *filename) {
	printf("editor: Loading %s\n", filename);
}

void EditorLineAdd(char *text) {

}

void EditorLineRemove(unsigned long long line_number) {

}

