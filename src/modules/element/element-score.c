#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#include "nexus.h"
#include "element.h"

static unsigned long long element_score_version = 3;
static unsigned long long element_score_version_found;
struct timeval tv_score_saved;
unsigned long long total_waste, total_battery, total_copper, total_gold,
	total_iron, total_magnet, total_rock, total_rubber, total_silver, total_wood;

void ElementScoreLoad(void) {
	if (verbose) printf("Loading element score\n");

	FILE *fp = fopen("element-score.dat", "rb");
	if (fp == NULL) {
		ElementScoreSave();
		return;
	}

	fseek(fp, 0, SEEK_END);
	long filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if (filesize <= 9*8) { // version 0.2.1 and earlier, V1
		fread(&total_waste, 8, 1, fp);
		fread(&total_battery, 8, 1, fp);
		fread(&total_copper, 8, 1, fp);
		fread(&total_gold, 8, 1, fp);
		fread(&total_iron, 8, 1, fp);
		fread(&total_magnet, 8, 1, fp);
		fread(&total_rock, 8, 1, fp);
		total_rubber = 0;
		fread(&total_silver, 8, 1, fp);
		fread(&total_wood, 8, 1, fp);
	}
	else if (filesize >= 10*8) { // version 0.2.2 and above
		fread(&element_score_version_found, 8, 1, fp);
		if (element_score_version_found == 2) {
			fread(&total_waste, 8, 1, fp);
			fread(&total_battery, 8, 1, fp);
			fread(&total_copper, 8, 1, fp);
			fread(&total_gold, 8, 1, fp);
			fread(&total_iron, 8, 1, fp);
			fread(&total_magnet, 8, 1, fp);
			fread(&total_rock, 8, 1, fp);
			total_rubber = 0;
			fread(&total_silver, 8, 1, fp);
			fread(&total_wood, 8, 1, fp);
		}
		else if (element_score_version_found == 3) {
			fread(&total_waste, 8, 1, fp);
			fread(&total_battery, 8, 1, fp);
			fread(&total_copper, 8, 1, fp);
			fread(&total_gold, 8, 1, fp);
			fread(&total_iron, 8, 1, fp);
			fread(&total_magnet, 8, 1, fp);
			fread(&total_rock, 8, 1, fp);
			fread(&total_rubber, 8, 1, fp);
			fread(&total_silver, 8, 1, fp);
			fread(&total_wood, 8, 1, fp);
		}
	}

	fclose(fp);
}

void ElementScoreSave(void) {
	
	FILE *fp = fopen("element-score.dat", "wb+");
	if (fp == NULL) {
		printf("nexus error: ElementScoreSave(): Cannot open element-score.dat: %s\n",
			strerror(errno));
		return;
	}

	fwrite(&element_score_version, 8, 1, fp);
	fwrite(&total_waste, 8, 1, fp);
	fwrite(&total_battery, 8, 1, fp);
	fwrite(&total_copper, 8, 1, fp);
	fwrite(&total_gold, 8, 1, fp);
	fwrite(&total_iron, 8, 1, fp);
	fwrite(&total_magnet, 8, 1, fp);
	fwrite(&total_rock, 8, 1, fp);
	fwrite(&total_rubber, 8, 1, fp);
	fwrite(&total_silver, 8, 1, fp);
	fwrite(&total_wood, 8, 1, fp);

	fclose(fp);
}
