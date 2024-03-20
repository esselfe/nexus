#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#include "nexus.h"
#include "element.h"

unsigned long long element_credits;

void ElementCreditLoad(void) {
	if (verbose) printf("Loading element credits\n");

	FILE *fp = fopen("element-credits.dat", "rb");
	if (fp == NULL) {
		ElementCreditSave();
		return;
	}

	fread(&element_credits, 8, 1, fp);
	
	fclose(fp);
}

void ElementCreditSave(void) {
	FILE *fp = fopen("element-credits.dat", "wb+");
	if (fp == NULL) {
		printf("nexus error: ElementCreditSave(): Cannot open element-credits.dat: %s\n",
			strerror(errno));
		return;
	}

	fwrite(&element_credits, 8, 1, fp);

	fclose(fp);
}
