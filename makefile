#based on: scottmcpeak.com/autodepend/autodepend.html
#if depencies are renamed a make clean will be required

_MAKEFILE_ABS = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
_TARGET := dnf
$(info makefile=$(_MAKEFILE_ABS))
.DEFAULT_GOAL = run
_MAKEFILE_DIR := $(dir $(_MAKEFILE_ABS))
#_MINGW32 = /d/msys32/mingw32
#_MINGW32_LIB = $(_MINGW32)/lib
#_MINGW32_INC = $(_MINGW32)/include

$(info make path=$(_MAKEFILE_DIR))
$(info target=$(_TARGET))
BDIR = bin
ODIR = obj
IDIR = .
INC = -I$(IDIR) -I../eventmgr/inc -I/d/Documents/c/absdatatypes/inc -I/d/Documents/c/zhash/inc
LIB = -L../eventmgr/lib -L../absdatatypes/lib -L../zhash/lib
LIBS = ../absdatatypes/lib/libabsdatatypes.a ../zhash/lib/libzhash.a
LIBS_SHORT = -leventmgr -labsdatatypes -lzhash -lallegro_monolith -lmingw32 -lz
SDIR = .
# -Wextra -Wpedantic 
CFLAGS = -static -Wall -W -ggdb -std=c99 $(INC) $(LIB)


# https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
_OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

_dummy := $(shell mkdir -p "$(BDIR)" "$(ODIR)")

clean_filenames := $(BDIR)/$(_TARGET).exe $(ODIR)/*.o $(ODIR)/*.d

#clean_files := $(strip $(foreach f,$(clean_filenames),$(wildcard $(f)))) $(LIBS)
clean_files := $(strip $(foreach f,$(clean_filenames),$(wildcard $(f))))


all: $(OBJS) $(LIBS)
	gcc $(OBJS) $(LIB) $(LIBS_SHORT) -o $(BDIR)/$(_TARGET)

run: all
	./$(BDIR)/$(_TARGET).exe

rundrm: all
	C:/dr_m/bin/drmemory -batch -- ./$(BDIR)/$(_TARGET).exe

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
$(ODIR)/%.o: $(SDIR)/%.c
	gcc -c $(CFLAGS) $*.c -o $(ODIR)/$*.o
	gcc -MM $(CFLAGS) $*.c > $(ODIR)/$*.d

#mingw32-make -C ../absdatatypes --file=makefiles/absdatatypes.makefile lib DEST=$(_MAKEFILE_DIR)$(LDIR) lib
../absdatatypes/lib/libabsdatatypes.a:
	mingw32-make -C ../absdatatypes

#mingw32-make -C ../zhash --file=makefiles/zhash.makefile lib DEST=$(_MAKEFILE_DIR)$(LDIR) lib
../zhash/lib/libzhash.a:
	mingw32-make -C ../zhash lib

# remove compilation products
clean:
ifneq ($(clean_files),)
	rm -f $(clean_files)
endif
