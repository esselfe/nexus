#ifndef FILE_BROWSER_H
#define FILE_BROWSER_H 1

#include <GL/gl.h>
#include "selectID.h"

#define ENTRY_TYPE_UNKNOWN    0
#define ENTRY_TYPE_DIRECTORY  1
#define ENTRY_TYPE_EXECUTABLE 2
#define ENTRY_TYPE_FILE       3

struct FileBrowserListEntry {
	struct FileBrowserListEntry *prev, *next;
	unsigned int type;
	unsigned int rank;
	struct SelectID *selectid;
	char *name;
};
struct FileBrowserList {
	struct FileBrowserListEntry *first_entry, *last_entry;
	unsigned long entry_total;
};
extern struct FileBrowserList file_browser_list;
extern struct FileBrowserListEntry *file_browser_selected_entry;
extern GLuint file_browser_select_buffer[100];

void FileBrowserInit(void);
void FileBrowserListAddEntry(unsigned int type, char *name);
void FileBrowserListLoad(char *path);
void FileBrowserListDestroy(void);
struct FileBrowserListEntry *FileBrowserListEntryByRank(unsigned int rank);
struct FileBrowserListEntry *FileBrowserListEntryBySelectID(GLuint id);
void FileBrowserPickingCheck(void);
void FileBrowserRender(void);

#endif /* FILE_BROWSER_H */