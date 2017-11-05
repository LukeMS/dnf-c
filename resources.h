#ifndef RESOURCES_H
#define RESOURCES_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct Resources_ Resources;
typedef struct Tileset_   Tileset;
#include "dnf.h"
#include "manager.h"

typedef struct Resources_ {
    Tileset* tileset;
} Resources;

typedef struct TileSource_ {
    char* file;
    char* name;
    int pos;
    int var;
} TileSource;

typedef struct Tileset_ {
    struct ZHashTable* tile_sources;
    struct ZHashTable* max_pos;
    struct ZHashTable* max_var;
    bool               use_cache;
} Tileset;

int init_resources(void);

int load_tilesets(void);

void unload_resources(void);

void unload_tilesets(Tileset** tileset);

#endif
