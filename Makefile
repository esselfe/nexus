-include config.mk

PROG := nexus

PKG_CONFIG ?= pkg-config

LIBS := gl sdl2 glu libpng
CFLAGS += $(shell $(PKG_CONFIG) --cflags $(LIBS)) -std=c17 -MMD -MP
CPPFLAGS += -D_GNU_SOURCE -Isrc/
LDLIBS += $(shell $(PKG_CONFIG) --libs $(LIBS)) -lm -lpthread
OBJDIR := obj
OBJ := args.o camera.o camera-goto.o camera-jump.o delta.o event.o flag.o floor.o \
	font.o hud.o image.o mode.o moon.o msg.o nexus.o render.o selectID.o sky.o \
	terminal.o window.o
include src/modules/file-browser/module.mk
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
