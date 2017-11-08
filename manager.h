#ifndef MANAGER_H
#define MANAGER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/*****************************************************************
 * forward struct declaration to enable cross-references
 ****************************************************************/
typedef struct Manager Manager;
#include "eventmgr.h"
#include "dnf.h"
#include "scene_base.h"
#include "resources.h"
#include "scene_splash.h"


int DNF_manager_run(void);

typedef struct Manager {
    int            (*run) (void);

    Resources*     resources;
    DNF_Scene*     scene;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *al_event_queue;

    EventMgr *events;

    unsigned int cmd_opt;
} Manager;

Manager* manager;

int new_Manager(void);

void del_Manager(void);

#endif
