
CFLAGS = -std=c11 -Wall -Werror -D_GNU_SOURCE -O2
LDFLAGS = -lSDL2 -lGLEW -lGL -lGLU
PROGNAME = nexus

.PHONY: all clean

default: all

all: $(PROGNAME)

$(PROGNAME): nexus.c
	gcc $(CFLAGS) $(LDFLAGS) nexus.c -o $(PROGNAME)

clean:
	@rm -v $(PROGNAME) 2>/dev/null || true

