#ifndef MANAGER_H
#define MANAGER_H

#include <stdint.h>
#include <stdlib.h>
#include "stdbool.h"

/*****************************************************************
 * forward struct declaration to enable cross-references
 ****************************************************************/
typedef struct Manager_ Manager;
#include "scene_base.h"
#include "resources.h"



typedef struct Manager_ {
    Resources* resources;
    Scene*     scene;
} Manager;
uint32_t Manager_ref_count;
Manager *manager;

bool new_Manager(Manager **manager_pp);

bool del_Manager(Manager *manager_p);

#endif
