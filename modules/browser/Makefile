
CFLAGS = -std=c11 -Wall -Werror -D_GNU_SOURCE -O2 -I../..
OBJDIR = ../../obj

default: all

all: $(OBJDIR)/browser-render.o

$(OBJDIR)/browser-render.o: render.c
	gcc -c $(CFLAGS) render.c -o $(OBJDIR)/browser-render.o

