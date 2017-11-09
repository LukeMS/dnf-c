_MAKEFILE_ABS = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
_TARGET := $(basename $(notdir $(realpath $(lastword $(_MAKEFILE_ABS)))))
ORIGIN = $(CURDIR)

$(info CURDIR=$(CURDIR))
$(info ORIGIN=$(ORIGIN))
$(info TRAVIS_BUILD_DIR=$(TRAVIS_BUILD_DIR))

BDIR = bin
SDIR = .
IDIR = -Iinc -I/usr/include -I/usr/include/absdt 
LDIR = -L/usr/lib 
LIBS = -leventmgr -labsdt -lzhash -lz
CFLAGS = -Wall -W -ggdb -std=c99
ALLEGRO_CFG = -I/usr/local/include -L/usr/local/lib/ -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_main -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf

_dummy := $(shell mkdir -p "$(BDIR)")

$(TRAVIS_BUILD_DIR)/allegro5:
	git clone https://github.com/liballeg/allegro5.git $(TRAVIS_BUILD_DIR)/allegro5
	mkdir $(TRAVIS_BUILD_DIR)/allegro5/build
	cd $(TRAVIS_BUILD_DIR)/allegro5/build
	cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DWANT_SHADERS_GL=$WANT_SHADERS_GL
	make


dep_allegro: $(TRAVIS_BUILD_DIR)/allegro5
	cd $(TRAVIS_BUILD_DIR)//allegro5/build
	sudo make install
	sudo ldconfig

dep_absdatatypes:
	git clone https://github.com/LukeMS/absdatatypes-c.git $(TRAVIS_BUILD_DIR)/absdatatypes
	make -C $(TRAVIS_BUILD_DIR)/absdatatypes --file=linux.makefile

dep_zhash:
	git clone https://github.com/LukeMS/zhash-c.git $(TRAVIS_BUILD_DIR)/zhash
	make -C $(TRAVIS_BUILD_DIR)/zhash --file=linux.makefile

dep_eventmgr:
	git clone https://github.com/LukeMS/eventmgr-c.git $(TRAVIS_BUILD_DIR)/eventmgr
	make -C $(TRAVIS_BUILD_DIR)/eventmgr --file=linux.makefile

all:
	gcc $(CFLAGS) *.c $(IDIR) $(LDIR) $(LIBS) $(ALLEGRO_CFG) -o $(BDIR)/$(_TARGET)

run: all
	$(BDIR)/$(_TARGET) NOINPUT

valgrind: all
	valgrind --error-exitcode=666 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --track-fds=yes $(BDIR)/$(_TARGET) NOINPUT

#gdb -batch -ex "run" -ex "bt" $(BDIR)/$(_TARGET) 2>&1 | grep -v ^"No stack."$
gdb: all
	gdb -batch -ex "directory /opt/src/glibc:/opt/src/glibc/stdlib" -ex "run" -ex "bt" $(BDIR)/$(_TARGET) NOINPUT 2>&1
