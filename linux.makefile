_MAKEFILE_ABS = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
_TARGET := $(basename $(notdir $(realpath $(lastword $(_MAKEFILE_ABS)))))

BDIR = bin
SDIR = .
IDIR = -Iinc -I/usr/include -I/usr/include/absdt
LDIR = -L/usr/lib
LIBS = -leventmgr -labsdt -lzhash -lz
CFLAGS = -static -Wall -W -ggdb -std=c99
ALLEGRO_CFG = `pkg-config --cflags --libs allegro-5.2 allegro_acodec-5.2 allegro_audio-5.2 allegro_color-5.2 allegro_dialog-5.2 allegro_font-5.2 allegro_image-5.2 allegro_main-5.2 allegro_memfile-5.2 allegro_physfs-5.2 allegro_primitives-5.2 allegro_ttf-5.2`

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
