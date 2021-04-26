
CFLAGS = -std=c11 -Wall -Werror -D_GNU_SOURCE -O2 -I../..
OBJDIR = ../../obj

default: all

all: $(OBJDIR)/memory-delta.o $(OBJDIR)/memory-render.o

$(OBJDIR)/memory-delta.o: delta.c
	gcc -c $(CFLAGS) delta.c -o $(OBJDIR)/memory-delta.o

$(OBJDIR)/memory-render.o: render.c
	gcc -c $(CFLAGS) render.c -o $(OBJDIR)/memory-render.o

