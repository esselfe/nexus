-include config.mk

PROG := nexus

PKG_CONFIG ?= pkg-config

LIBS := gl sdl2 glew glu libpng
CFLAGS += $(shell $(PKG_CONFIG) --cflags $(LIBS)) -std=c11 -MMD -MP -Isrc/
CPPFLAGS += -D_GNU_SOURCE
LDLIBS += $(shell $(PKG_CONFIG) --libs $(LIBS)) -lm -lpthread
OBJDIR := obj
OBJ := camera.o delta.o event.o flag.o floor.o font.o image.o nexus.o render.o \
	sky.o state.o terminal.o
include src/modules/browser/module.mk
include src/modules/editor/module.mk
include src/modules/element/module.mk
include src/modules/memory/module.mk
OBJ := $(addprefix $(OBJDIR)/,$(OBJ))
DEP := $(OBJ:.o=.d)
VPATH += src

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

all: $(PROG)

$(PROG): $(OBJ)
	$(LINK.o) $^ $(LDLIBS) -o $@

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

clean:
	$(RM) -v $(OBJ) $(DEP) config.mk $(PROG)
	$(RM) -dv $(OBJDIR)

-include $(DEP)

.PHONY: all clean
