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


dep_allegro_build:
	cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DWANT_SHADERS_GL=$WANT_SHADERS_GL
	make -C $(TRAVIS_BUILD_DIR)/allegro5/build/ --file=Makefile

$(TRAVIS_BUILD_DIR)/allegro5/build/linux.makefile:
	git clone https://github.com/liballeg/allegro5.git $(TRAVIS_BUILD_DIR)/allegro5
	mkdir $(TRAVIS_BUILD_DIR)/allegro5/build
	cp linux.makefile $(TRAVIS_BUILD_DIR)/allegro5/build/
	make -C $(TRAVIS_BUILD_DIR)/allegro5/build/ --file=$(TRAVIS_BUILD_DIR)/allegro5/build/linux.makefile


dep_allegro: $(TRAVIS_BUILD_DIR)/allegro5/build/linux.makefile
	sudo make -C $(TRAVIS_BUILD_DIR)/allegro5/build/ --file=Makefile install
	cd $(TRAVIS_BUILD_DIR)/allegro5/build && sudo ldconfig

dep_absdatatypes:
	git clone https://github.com/LukeMS/absdatatypes-c.git $(TRAVIS_BUILD_DIR)/absdatatypes
	sudo make -C $(TRAVIS_BUILD_DIR)/absdatatypes --file=$(TRAVIS_BUILD_DIR)/absdatatypes/linux.makefile install

dep_zhash:
	git clone https://github.com/LukeMS/zhash-c.git $(TRAVIS_BUILD_DIR)/zhash
	sudo make -C $(TRAVIS_BUILD_DIR)/zhash --file=$(TRAVIS_BUILD_DIR)/zhash/linux.makefile install

dep_eventmgr:
	git clone https://github.com/LukeMS/eventmgr-c.git $(TRAVIS_BUILD_DIR)/eventmgr
	sudo make -C $(TRAVIS_BUILD_DIR)/eventmgr --file=$(TRAVIS_BUILD_DIR)/eventmgr/linux.makefile install

all:
	gcc $(CFLAGS) *.c $(IDIR) $(LDIR) $(LIBS) $(ALLEGRO_CFG) -o $(BDIR)/$(_TARGET)

run: all
	$(BDIR)/$(_TARGET) NOINPUT

valgrind: all
	valgrind --error-exitcode=666 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --track-fds=yes $(BDIR)/$(_TARGET) NOINPUT

#gdb -batch -ex "run" -ex "bt" $(BDIR)/$(_TARGET) 2>&1 | grep -v ^"No stack."$
gdb: all
	gdb -batch -ex "directory /opt/src/glibc:/opt/src/glibc/stdlib" -ex "run" -ex "bt" $(BDIR)/$(_TARGET) NOINPUT 2>&1
