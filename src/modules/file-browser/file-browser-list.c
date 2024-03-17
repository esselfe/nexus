#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <GL/gl.h>

#include "nexus.h"

struct FileBrowserList file_browser_list;
struct FileBrowserListEntry *file_browser_selected_entry;

void FileBrowserListAddEntry(unsigned int type, char *name) {
	struct FileBrowserListEntry *entry = malloc(sizeof(struct FileBrowserListEntry));
	if (file_browser_list.entry_total == 0) {
		entry->prev = NULL;
		entry->rank = 1;
		file_browser_list.first_entry = entry;
	}
	else {
		entry->prev = file_browser_list.last_entry;
		entry->rank = entry->prev->rank + 1;
		file_browser_list.last_entry->next = entry;
	}
	entry->type = type;
	entry->next = NULL;
	entry->name = malloc(strlen(name)+1);
	sprintf(entry->name, "%s", name);
	entry->selectid = SelectIDNew();

	++file_browser_list.entry_total;
	file_browser_list.last_entry = entry;
}

void FileBrowserListLoad(char *path) {
	if (verbose) printf("  Loading %s\n", path);

	DIR *dir = opendir(path);
	if (dir == NULL) {
		printf("nexus:%s:%s error: Cannot open %s: %s\n", __FILE__, __FUNCTION__,
			path, strerror(errno));
		return;
	}

	struct dirent *dent;
	while (1) {
		errno = 0;
		dent = readdir(dir);
		if (dent == NULL)
			break;
		
		if (dent->d_name != NULL && strcmp(dent->d_name, ".") == 0)
			continue;
		
		if (dent->d_type == DT_DIR)
			FileBrowserListAddEntry(ENTRY_TYPE_DIRECTORY, dent->d_name);
		else if (dent->d_type == DT_REG) {
			struct stat st;
			stat(dent->d_name, &st);
			if (st.st_mode & S_IXUSR || st.st_mode & S_IXGRP ||
				st.st_mode & S_IXOTH)
				FileBrowserListAddEntry(ENTRY_TYPE_EXECUTABLE, dent->d_name);
			else
				FileBrowserListAddEntry(ENTRY_TYPE_FILE, dent->d_name);
		}
		else
			FileBrowserListAddEntry(ENTRY_TYPE_UNKNOWN, dent->d_name);
	}

	closedir(dir);
}

void FileBrowserListDestroy(void) {
	struct FileBrowserListEntry *entry = file_browser_list.last_entry;
	if (entry == NULL)
		return;
	
	while (1) {
		free(entry->name);

		if (entry->prev != NULL) {
			entry = entry->prev;
			free(entry->next);
		}
		else {
			free(entry);
			break;
		}
	}
}

struct FileBrowserListEntry *FileBrowserListEntryByRank(unsigned int rank) {
	struct FileBrowserListEntry *entry = file_browser_list.first_entry;
	if (entry == NULL)
		return NULL;
	
	while (1) {
		if (entry->rank == rank)
			return entry;
		
		if (entry->next != NULL)
			entry = entry->next;
		else
			break;
	}
	
	return NULL;
}

struct FileBrowserListEntry *FileBrowserListEntryBySelectID(GLuint id) {
	struct FileBrowserListEntry *entry = file_browser_list.first_entry;
	if (entry == NULL)
		return NULL;
	
	while (1) {
		if (entry->selectid->id == id)
			return entry;
		
		if (entry->next != NULL)
			entry = entry->next;
		else
			break;
	}
	
	return NULL;
}
