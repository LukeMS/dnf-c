#ifndef SCENE_BASE_H
#define SCENE_BASE_H

typedef struct Scene_ Scene;
#include "Manager.h"


typedef struct Scene_ {

    void *derived;
} Scene;

#endif
