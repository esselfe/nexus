#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "nexus.h"
#include "floor.h"
#include "window.h"

// Structure of getopt options for program options and arguments processing
static const struct option long_options[] = {
	{"help", no_argument, NULL, 'h'},
	{"version", no_argument, NULL, 'V'},
	{"verbose", no_argument, NULL, 'v'},
	{"floor-factor", required_argument, NULL, 'f'},
	{"position-x", required_argument, NULL, 'X'},
	{"position-y", required_argument, NULL, 'Y'},
	{"width", required_argument, NULL, 'W'},
	{"height", required_argument, NULL, 'H'},
	{NULL, 0, NULL, 0}
};
static const char *short_options = "hVvf:X:Y:W:H:";

void ArgsParse(int *argc_p, char **argv_p) {
    int c;
	while (1) {
		c = getopt_long(*argc_p, argv_p, short_options, long_options, NULL);
		if (c == -1)
			break;
		
		switch (c) {
		case 'h': // --help
			ShowHelp();
			exit(0);
		case 'V': // --version
			ShowVersion();
			exit(0);
		case 'v': // --verbose
			verbose = 1;
			break;
		case 'f': // --floor-factor
			if (optarg != NULL)
				floor_factor = atoi(optarg);
			
			if (floor_factor <= 0)
				floor_factor = 1;
			break;
		case 'X': // --position-x
			if (optarg != NULL)
				winX = atoi(optarg);
			break;
		case 'Y': // --position-y
			if (optarg != NULL)
				winY = atoi(optarg);
			break;
		case 'W': // --width
			if (optarg != NULL)
				winW = atoi(optarg);
			break;
		case 'H': // --height
			if (optarg != NULL)
				winH = atoi(optarg);
			break;
		default:
			printf("nexus error: Unknown argument: %c (%d)\n", (char)c, c);
			break;
		}
	}
}

