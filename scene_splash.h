#ifndef SCENE_SPLASH
#define SCENE_SPLASH_H value

#include "scene_base.h"

/*****************************************************************************
*                                                                            *
*  Implement DNF_SceneSplash as DNF_Scene.                                   *
*                                                                            *
*****************************************************************************/
typedef DNF_Scene DNF_SceneSplash;

int DNF_scene_splash_load(DNF_Scene* scene, void* data);
int DNF_scene_splash_update(DNF_Scene* scene);
int DNF_scene_splash_draw(DNF_Scene* scene);
int DNF_scene_splash_unload(DNF_Scene* scene);

#define DNF_scene_splash_init(scene) \
    do { \
        DNF_scene_base_init(scene); /* 'super' */ \
        scene->update = DNF_scene_splash_update; \
    } while (0)



#endif