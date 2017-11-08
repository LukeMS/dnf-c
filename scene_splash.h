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
int DNF_scene_splash_update(void* data);
int DNF_scene_splash_draw(void* data);
int DNF_scene_splash_unload(DNF_Scene* scene);

DNF_Scene* DNF_scene_splash_init(void);


#endif