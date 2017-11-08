_MAKEFILE_ABS = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
_TARGET := $(basename $(notdir $(realpath $(lastword $(_MAKEFILE_ABS)))))

BDIR = bin
SDIR = .
IDIR = -Iinc -I/usr/include -I/usr/include/absdt -I/usr/local/include
LDIR = -L/usr/lib -L/usr/local/lib/
LIBS = -leventmgr -labsdt -lzhash -lz
CFLAGS = -static -Wall -W -ggdb -std=c99
ALLEGRO_CFG = `pkg-config --cflags --libs` -lallegro-static -lallegro_acodec-static -lallegro_audio-static -lallegro_color-static -lallegro_dialog-static -lallegro_font-static -lallegro_image-static -lallegro_main-static -lallegro_memfile-static -lallegro_physfs-static -lallegro_primitives-static -lallegro_ttf-static

_dummy := $(shell mkdir -p "$(BDIR)")

all:
	gcc $(CFLAGS) *.c $(IDIR) $(LDIR) $(LIBS) $(ALLEGRO_CFG) -o $(BDIR)/$(_TARGET)

run: all
	$(BDIR)/$(_TARGET) NOINPUT

valgrind: all
	valgrind --error-exitcode=666 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --track-fds=yes $(BDIR)/$(_TARGET) NOINPUT

#gdb -batch -ex "run" -ex "bt" $(BDIR)/$(_TARGET) 2>&1 | grep -v ^"No stack."$
gdb: all
	gdb -batch -ex "directory /opt/src/glibc:/opt/src/glibc/stdlib" -ex "run" -ex "bt" $(BDIR)/$(_TARGET) NOINPUT 2>&1
