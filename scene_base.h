#ifndef SCENE_BASE_H
#define SCENE_BASE_H

typedef struct DNF_Scene DNF_Scene;
#include "manager.h"


typedef struct DNF_Scene {

    int (*load)   (DNF_Scene* scene, void* newdata);
    int (*update) (DNF_Scene* scene);
    int (*draw)   (DNF_Scene* scene);
    int (*unload) (DNF_Scene* scene);

    void* data;


} DNF_Scene;

#define DNF_scene_base_init(scene) \
    do { \
        scene->load = NULL; \
        /* initialize tileset's hash tables */ \
        scene->data = zcreate_hash_table(); \
    } while (0)

#endif
