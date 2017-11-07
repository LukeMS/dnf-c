#include <assert.h>

#include "dnfutil.h"
#include "resources.h"
#include "rectpacker.h"

int init_resources(void) {
    // allocate memory for and check manager->resources
    if (!(manager->resources = calloc(1, sizeof(*(manager->resources)))))
        return -1;

    if (load_tilesets())
        return -1;

    return 0;
}

void unload_resources(void) {
    unload_tilesets(&manager->resources->tileset);

    return;
}

static void free_tile_source_members(TileSource* ptr) {
    free(ptr->file);
    free(ptr->name);
}

void unload_tilesets(Tileset** tileset) {
    for (struct ZHashEntry* tile_source = (*tileset)->tile_sources->head;
         tile_source;
         tile_source = tile_source->lnknext) {

        free_tile_source_members(tile_source->val);
        free(tile_source->val);
    }

    zfree_hash_table((*tileset)->tile_sources);
    zfree_hash_table((*tileset)->max_pos);
    zfree_hash_table((*tileset)->max_var);

    return;
}


static TileSource* create_tile_source(const char* path) {
    // allocate a new struct
    TileSource* tile_source;
    if (!(tile_source = calloc(1, sizeof(*tile_source))))
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

    if (!(tile_source->file = calloc(strlen(path) + 1, 1)))
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

static int list_tile_files(const char* path, struct ZHashTable* sources,
        long unsigned int* adler) {
    char* name; // name of each file during iteration
    char* tile_key; // key that will be used to hash
    TileSource* tile_src = NULL;
    uint32_t fmtime_v; // mod. time of each file
    *adler = adler32(0L, Z_NULL, 0); // Adler-32 checksum

    assert(sources->entry_count == 0);

    ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(path);
    if(al_open_directory(dir)) {
        ALLEGRO_FS_ENTRY* file;
        while((file = al_read_directory(dir))) {
            name = (char*)al_get_fs_entry_name(file);
            if (!strcmp(get_file_ext(name), "png")) {

                tile_src = create_tile_source(name);
                tile_key = create_tile_key(tile_src);
                zhash_set(sources, tile_key, (void *) tile_src);

                // adler consider bytes [0..len-1], so we pass the full length of a string
                *adler = adler32(*adler, (const unsigned char*) tile_key,
                                       strlen(tile_key));

                fmtime_v = fmtime(name);

                // adler consider bytes [0..len-1], so we pass the size of the number + 1
                *adler = adler32(*adler, (const unsigned char*) &fmtime_v, sizeof(fmtime_v) + 1);

                // zhash keeps its own strcpy of the key
                free(tile_key);
            }
            al_destroy_fs_entry(file);
        }
    } else
        return -1;

    assert(sources->entry_count > 0);

    if (DNF_DEBUG >= 1) {
        dnf_info("adler32 %lu", *adler);
    }

    al_destroy_fs_entry(dir);

    return 0;
}

int load_tilesets(void) {

    long unsigned int checksum = 0;
    Tileset* tileset;
    if (!(tileset = calloc(1, sizeof(*tileset))))
        dnf_abort("failed to allocate memory to manager->resources->tileset");
    manager->resources->tileset = tileset;

    // initialize tileset's hash tables
    tileset->tile_sources = zcreate_hash_table();
    tileset->max_pos      = zcreate_hash_table();
    tileset->max_var      = zcreate_hash_table();

    // list all the files and calculate a checksum
    list_tile_files("resources/gfx/tile_feature",
                    tileset->tile_sources,
                    &checksum);
    dnf_info("checksum %lu", checksum);

    if (DNF_DEBUG == 4) {
        for (struct ZHashEntry* p = tileset->tile_sources->head;
             p;
             p = p->lnknext)
        {
            dnf_info("(%s)%s#%.3d#%.3d", ((TileSource*) p->val)->file,
                                           ((TileSource*) p->val)->name,
                                           ((TileSource*) p->val)->pos,
                                           ((TileSource*) p->val)->var
                   );
        }
    }

    /* TODO:
    - CHECK CHECKSUM
    - IF CACHE IS UP-TO-DATE, USE IT
    - ELSE, CREATE A NEW ATLAS AND STORE THE CHECKSUM
    */

    int packer_h;

    if (rectpacker.imgpacker(1, tileset->tile_sources, &packer_h)) {
        dnf_abort("img_packer returned an error.");
    } else {
        dnf_info("packer_h %d", packer_h);

    }

    return 0;
}


