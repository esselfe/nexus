
CFLAGS = -std=c11 -Wall -Werror -D_GNU_SOURCE -O2
LDFLAGS = -lSDL2 -lGLEW -lGL -lGLU
OBJDIR = obj
OBJS = $(OBJDIR)/event.o $(OBJDIR)/flag.o $(OBJDIR)/font.o \
$(OBJDIR)/image.o $(OBJDIR)/nexus.o $(OBJDIR)/render.o $(OBJDIR)/state.o
PROGNAME = nexus

.PHONY: all prepare clean

default: all

all: prepare $(OBJS) $(PROGNAME)
	@ls -li --color=auto $(PROGNAME) 2>/dev/null || true

prepare:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR) 2>/dev/null

$(OBJDIR)/event.o: event.c
	gcc -c $(CFLAGS) event.c -o $(OBJDIR)/event.o

$(OBJDIR)/flag.o: flag.c
	gcc -c $(CFLAGS) flag.c -o $(OBJDIR)/flag.o

$(OBJDIR)/font.o: font.c
	gcc -c $(CFLAGS) font.c -o $(OBJDIR)/font.o

$(OBJDIR)/image.o: image.c
	gcc -c $(CFLAGS) image.c -o $(OBJDIR)/image.o

$(OBJDIR)/nexus.o: nexus.h nexus.c
	gcc -c $(CFLAGS) nexus.c -o $(OBJDIR)/nexus.o

$(OBJDIR)/render.o: render.c
	gcc -c $(CFLAGS) render.c -o $(OBJDIR)/render.o

$(OBJDIR)/state.o: state.c
	gcc -c $(CFLAGS) state.c -o $(OBJDIR)/state.o

$(PROGNAME): $(OBJS)
	gcc $(LDFLAGS) $(OBJS) -o $(PROGNAME)

clean:
	@rm -rv $(OBJDIR) $(PROGNAME) 2>/dev/null || true

