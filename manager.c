#include "manager.h"

uint32_t Manager_ref_count = 0;

int new_Manager(void)
{
    // allocate memory for and check manager
    // calloc takes care of initializing pointers to NULL
    if (!(manager = calloc(1, sizeof(*manager))))
        return -1;

    manager->run    = DNF_manager_run;
    manager->events = EventMgr_create();
    manager->scene  = DNF_scene_splash_init();

    return 0;
}

void del_Manager(void) {
    EventMgr_destroy(manager->events);

    free(manager);

    return;
}

int DNF_manager_run(void) {
    dnf_info("called DNF_manager_run");

    manager->scene->load(manager->scene, NULL);

    DNF_SceneEvt *scene_evt = calloc(1, sizeof(*scene_evt));

    int loops = 0;
    // al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
    while (1) {
        ALLEGRO_EVENT ev;

        /* al_init_timeout initializes a previously defined ALLEGRO_TIMEOUT object. In this case we are initializing it to 0.06 seconds from now, or 60 milliseconds in the future.*/
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);

        /* We tell Allegro to wait till an event arrives, or until the time out defined previously has elapsed, which ever occurs first. al_wait_for_event_until will return false if it didn't return an event before the timeout. */
        bool get_event = al_wait_for_event_until(manager->al_event_queue,
                                                 &ev, &timeout);

        /* Here we check if we received an event in the event queue. If it is a Display close event, we break out of the program loop. */
        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
      }
        al_clear_to_color(al_map_rgb(0, 0, 0));

        scene_evt->scene = manager->scene;
        // update scene
        manager->events->trigger(manager->events, "UPDATE", scene_evt);
        manager->events->trigger(manager->events, "DRAW",   scene_evt);

        al_flip_display();

        if (manager->cmd_opt & DNF_CMD_NOINPUT)
            break;
    }

    free(scene_evt);

    return 0;
}
