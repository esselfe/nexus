
CFLAGS = -std=c11 -Wall -Werror -D_GNU_SOURCE -O2
LDFLAGS = -lSDL2 -lGLEW -lGL -lGLU
OBJDIR = obj
OBJS = $(OBJDIR)/event.o $(OBJDIR)/nexus.o $(OBJDIR)/render.o
PROGNAME = nexus

.PHONY: all prepare clean

default: all

all: prepare $(OBJS) $(PROGNAME)

prepare:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR) 2>/dev/null

$(OBJDIR)/event.o: event.c
	gcc -c $(CFLAGS) event.c -o $(OBJDIR)/event.o

$(OBJDIR)/nexus.o: nexus.h nexus.c
	gcc -c $(CFLAGS) nexus.c -o $(OBJDIR)/nexus.o

$(OBJDIR)/render.o: render.c
	gcc -c $(CFLAGS) render.c -o $(OBJDIR)/render.o

$(PROGNAME): $(OBJS)
	gcc $(LDFLAGS) $(OBJS) -o $(PROGNAME)

clean:
	@rm -rv $(OBJDIR) $(PROGNAME) 2>/dev/null || true

