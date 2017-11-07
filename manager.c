#include "manager.h"

uint32_t Manager_ref_count = 0;

int new_Manager(void)
{
    // allocate memory for and check manager
    if (!(manager = calloc(1, sizeof(*manager))))
        return -1;

    manager->run         = DNF_manager_run;
    // calloc takes care of initializing NULL pointers
    //      manager->display     = NULL;
    //      manager->event_queue = NULL;
    //      (...)

    return 0;
}

void del_Manager(void) {
    free(manager);

    return;
}

int DNF_manager_run(void) {
    dnf_info("called DNF_manager_run");

    return 0;
}
