#include "manager.h"

uint32_t Manager_ref_count = 0;

bool new_Manager(Manager **manager_pp)
{
    *manager_pp = malloc(sizeof(**manager_pp));
    //Manager *manager_p = *manager_pp; // do something with it
    Manager_ref_count++;

    return 0;
}

bool del_Manager(Manager *manager_p) {
    free(manager_p);

    return 0;
}
