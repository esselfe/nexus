-include config.mk

PROG := nexus

PKG_CONFIG ?= pkg-config

LIBS := gl sdl2 glew glu
CFLAGS += $(shell $(PKG_CONFIG) --cflags $(LIBS)) -std=c11 -MMD -MP -I.
CPPFLAGS += -D_GNU_SOURCE
LDLIBS += $(shell $(PKG_CONFIG) --libs $(LIBS)) -lm
OBJDIR := obj
OBJ := camera.o delta.o event.o flag.o font.o image.o nexus.o render.o sky.o \
	state.o terminal.o
include modules/editor/module.mk
include modules/memory/module.mk
include modules/browser/module.mk
OBJ := $(addprefix $(OBJDIR)/,$(OBJ))
DEP := $(OBJ:.o=.d)

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

all: $(PROG)

$(PROG): $(OBJ)
	$(LINK.o) $^ $(LDLIBS) -o $@

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

clean:
	$(RM) -v $(OBJ) $(DEP) $(PROG)
	$(RM) -dv $(OBJDIR)

-include $(DEP)

.PHONY: all clean
