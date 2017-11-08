#ifndef SCENE_BASE_H
#define SCENE_BASE_H

typedef struct DNF_Scene DNF_Scene;
#include "manager.h"


typedef struct DNF_Scene {
    int (*load)   (DNF_Scene* scene, void* newdata);
    int (*update) (void* data);
    int (*draw)   (void* data);
    int (*unload) (DNF_Scene* scene);

    void* data;

} DNF_Scene;

typedef struct DNF_SceneEvt {
    DNF_Scene* scene;
    void* data;
} DNF_SceneEvt;

DNF_Scene* DNF_scene_base_init(void);

#endif
