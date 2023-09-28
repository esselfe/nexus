#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <GL/gl.h>

#include "nexus.h"

struct BrowserList browser_list;
struct BrowserListEntry *browser_selected_entry;

void BrowserListAddEntry(char *name) {
	struct BrowserListEntry *entry = malloc(sizeof(struct BrowserListEntry));
	if (browser_list.entry_total == 0) {
		entry->prev = NULL;
		entry->rank = 1;
		browser_list.first_entry = entry;
	}
	else {
		entry->prev = browser_list.last_entry;
		entry->rank = entry->prev->rank + 1;
		browser_list.last_entry->next = entry;
	}
	entry->next = NULL;
	entry->name = malloc(strlen(name)+1);
	sprintf(entry->name, "%s", name);

	++browser_list.entry_total;
	browser_list.last_entry = entry;
}

void BrowserListLoad(char *path) {
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
		if (dent == NULL) {
			if (errno)
				printf("nexus:%s:%s error: Cannot readdir(): %s\n", __FILE__, __FUNCTION__,
					strerror(errno));
			else
				break;
		}
		if (strcmp(dent->d_name, ".") == 0)
			continue;
		else
			BrowserListAddEntry(dent->d_name);
	}

	closedir(dir);
}

void BrowserListDestroy(void) {
	struct BrowserListEntry *entry = browser_list.last_entry;
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

struct BrowserListEntry *BrowserListEntryByRank(unsigned int rank) {
	struct BrowserListEntry *entry = browser_list.first_entry;
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
}

