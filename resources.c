#include <assert.h>

#include "dnfutil.h"
#include "resources.h"
#include "rectpacker.h"

int init_resources(void) {
    Resources* resources = NULL;
    if (!(resources = malloc(sizeof(*resources))))
        return -1;
    manager->resources = resources;

    if (load_tilesets())
        return -1;

    return 0;
}

void unload_resources(void) {
    unload_tilesets(&manager->resources->tileset);

    return;
}

void unload_tilesets(Tileset** tileset) {
    zfree_hash_table((*tileset)->tile_sources);
    zfree_hash_table((*tileset)->max_pos);
    zfree_hash_table((*tileset)->max_var);

    return;
}

static void free_tile_source_members(TileSource* ptr) {
    free(ptr->name);
    free(ptr->file);
}

static TileSource* create_tile_source(const char* path) {
    // allocate a new struct
    TileSource* tile_source;
    if (!(tile_source = malloc(sizeof(tile_source))))
        dnf_abort("failed to allocate memory");

    // Locate Last Occurrence of Character in String
    char *start = strrchr(path, '\\');
    
    // Locate First Occurrence of Character in String
    char *end = strchr(path, '#');

    // pointer arithmetic to the distance as an index
    int name_size = end - (++start);

    if (!(tile_source->name = calloc(name_size + 1, 1)))
        dnf_abort("failed to allocate memory");
    // copy a substring of length name_size from path into name
    strncpy(tile_source->name, start, name_size);

    if (!(tile_source->file = malloc(strlen(path) + 1)))
        dnf_abort("failed to allocate memory");;
    strcpy(tile_source->file, path);

    sscanf(end, "#p_%d#v_%d", &tile_source->pos, &tile_source->var);

    return tile_source;
}

static char* create_tile_key(TileSource* tile_source) {
    int name_size = strlen(tile_source->name) + 1 + // name + 1('#'')
                                           3  + 1 + // +3(pos000) + 1('#'')
                                           3;       // +3(var000)
    char* k = calloc(name_size + 1, 1);

    assert(sprintf(k, "%s#%.3d#%.3d", tile_source->name,
                                      tile_source->pos,
                                      tile_source->var) == name_size);

    return k;

}

static int load_tile_files(const char* path, struct ZHashTable* sources) {
    // name of each file during iteration
    char *name;

    // modification date of each file during iteration
    uint32_t fmtime_v;

    // running Adler-32 checksum
    long unsigned int adler = adler32(0L, Z_NULL, 0);

    TileSource* tile_source = NULL;

    char * tile_key;

    ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(path);
    if(al_open_directory(dir)) {
        ALLEGRO_FS_ENTRY* file;
        while((file = al_read_directory(dir))) {
            name = (char*)al_get_fs_entry_name(file);
            if (!strcmp(get_file_ext(name), "png")) {

                tile_source = create_tile_source(name);
                tile_key = create_tile_key(tile_source);
                zhash_set(sources, tile_key, (void *) tile_source);
                //zhash_set(sources, "a", (void *) "a");
                /*
                printf("tile: %s -> %s#%.3d#%.3d\n", tile_source->file,
                                                     tile_source->name,
                                                     tile_source->pos,
                                                     tile_source->var);
                */

                // zhash keeps its own strcpy of the key
                //free(tile_key);

                // adler consider bytes [0..len-1], so we pass the full length of a string
                adler = adler32(adler, (const unsigned char*) tile_key,
                                       strlen(tile_key));

                fmtime_v = fmtime(name);

                // adler consider bytes [0..len-1], so we pass the size of the number + 1
                adler = adler32(adler, (const unsigned char*) &fmtime_v, sizeof(fmtime_v) + 1);
            }
            al_destroy_fs_entry(file);
        }
    } else
        return -1;

    printf("adler32 %lu\n", adler); // 1694198809
    al_destroy_fs_entry(dir);

    return 0;

}

int load_tilesets(void) {

    Tileset* tileset;
    if (!(tileset = malloc(sizeof(*tileset))))
        dnf_abort("failed to allocate memory to manager->resources->tileset");
    manager->resources->tileset = tileset;

    // initialize tileset's hash tables
    tileset->tile_sources = zcreate_hash_table();
    tileset->max_pos      = zcreate_hash_table();
    tileset->max_var      = zcreate_hash_table();


    load_tile_files("resources/gfx/tile_feature", tileset->tile_sources);

    /*
    CHECK CHECKSUM
    IF CACHE IS UP-TO-DATE, USE IT
    IF NOT, CREATE A NEW ATLAS AND STORE THE CHECKSUM

    int packer_h = 0;
    int* packer_h_ptr = &packer_h;
    void* sources = manager;
    if (rectpacker.imgpacker(1, sources, &packer_h_ptr)) {
        dnf_abort("img_packer returned an error.");
    } else {
        printf("packer_h %d\n", packer_h);

    }
    */

    return 0;
}


