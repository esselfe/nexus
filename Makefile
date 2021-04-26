
CFLAGS = -std=c11 -Wall -Werror -D_GNU_SOURCE -O2
LDFLAGS = -lSDL2 -lGLEW -lGL -lGLU -lm
OBJDIR = obj
OBJS = $(OBJDIR)/camera.o $(OBJDIR)/delta.o $(OBJDIR)/event.o \
$(OBJDIR)/flag.o $(OBJDIR)/font.o $(OBJDIR)/image.o $(OBJDIR)/nexus.o \
$(OBJDIR)/render.o $(OBJDIR)/sky.o $(OBJDIR)/state.o $(OBJDIR)/terminal.o
MODOBJS = $(OBJDIR)/browser-render.o $(OBJDIR)/editor-render.o \
$(OBJDIR)/memory-delta.o $(OBJDIR)/memory-render.o
PROGNAME = nexus

.PHONY: all modules prepare clean

default: all

all: prepare $(OBJS) modules $(PROGNAME)
	@ls -li --color=auto $(PROGNAME) 2>/dev/null || true

modules:
	make -C modules

prepare:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR) 2>/dev/null

$(OBJDIR)/camera.o: camera.c
	gcc -c $(CFLAGS) camera.c -o $(OBJDIR)/camera.o

$(OBJDIR)/delta.o: delta.c
	gcc -c $(CFLAGS) delta.c -o $(OBJDIR)/delta.o

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

$(OBJDIR)/sky.o: sky.c
	gcc -c $(CFLAGS) sky.c -o $(OBJDIR)/sky.o

$(OBJDIR)/state.o: state.c
	gcc -c $(CFLAGS) state.c -o $(OBJDIR)/state.o

$(OBJDIR)/terminal.o: terminal.c
	gcc -c $(CFLAGS) terminal.c -o $(OBJDIR)/terminal.o

$(PROGNAME): $(OBJS) $(MODOBJS)
	gcc $(OBJDIR)/*.o -o $(PROGNAME) $(LDFLAGS)

clean:
	@rm -rv $(OBJDIR) $(PROGNAME) 2>/dev/null || true

