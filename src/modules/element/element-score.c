#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#include "nexus.h"

struct timeval tv_score_saved;

void ElementScoreLoad(void) {
	if (verbose) printf("Loading element score\n");

	FILE *fp = fopen("element-score.dat", "rb");
	if (fp == NULL) {
		ElementScoreSave();
		return;
	}

	fread(&total_waste, 8, 1, fp);
	fread(&total_iron, 8, 1, fp);
	fread(&total_wood, 8, 1, fp);
	fread(&total_magnet, 8, 1, fp);
	fread(&total_rock, 8, 1, fp);

	fclose(fp);
}

void ElementScoreSave(void) {
	if (verbose) printf("Saving element score\n");
	
	FILE *fp = fopen("element-score.dat", "wb+");
	if (fp == NULL) {
		printf("nexus error: ElementScoreSave(): Cannot open element-score.dat: %s\n",
			strerror(errno));
		return;
	}

	fwrite(&total_waste, 8, 1, fp);
	fwrite(&total_iron, 8, 1, fp);
	fwrite(&total_wood, 8, 1, fp);
	fwrite(&total_magnet, 8, 1, fp);
	fwrite(&total_rock, 8, 1, fp);

	fclose(fp);
}
