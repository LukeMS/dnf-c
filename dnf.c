#include "dnf.h"


Manager *manager = NULL;
//ALLEGRO_TEXTLOG* dnf_log_window = NULL;

void zhash_testy()
{
    struct ZHashTable *hash_table;
    hash_table = zcreate_hash_table();

    zhash_set(hash_table, "hello", (void *) "world");

    if (zhash_exists(hash_table, "hello")) {
        dnf_info("hello %s", (char *) zhash_get(hash_table, "hello"));
    }

    zfree_hash_table(hash_table);

    return;
}

void _dnf_free(void) {
    dnf_alert("called");

    if (manager->display != NULL)
        al_destroy_display(manager->display);
    if (manager->event_queue != NULL)
        al_destroy_event_queue(manager->event_queue);
    al_uninstall_system();

    unload_resources();
    del_Manager();
}

void dnf_init(void) {
    dnf_alert("called");

    zhash_testy();


    if (new_Manager())
        dnf_abort("failed to initialize 'manager'");

    if (!al_init())
        dnf_abort("Failed to initialize Allegro.");

    ALLEGRO_DISPLAY_MODE   disp_data;
    // minimum resolution
    al_get_display_mode(0, &disp_data);

    // maximum resolution
    // al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

    // al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    manager->display = al_create_display(disp_data.width, disp_data.height);
    if(manager->display == NULL) {
        dnf_abort("failed to create display.");
    }

    /*al_map_rgb takes three arguments, the value for the red, green, and blue components of the color respectively, and will return a ALLEGRO_COLOR structure. al_clear_to_color clears the current display [1] to a given color.*/
    al_clear_to_color(al_map_rgb(255, 255, 255));

    /*Allegro, by default, creates two image buffers -- the one being displayed on the screen, and the one being drawn on in the code. When you have finished drawing to one of the image buffers for one loop, then you are ready to display its result to the screen for the user. al_flip_display is called to swap the two image buffers around so that the first image buffer is now displayed to the user while the second image buffer becomes the one you will draw on. Failing to call this function will result in only the single, blank image buffer being shown on the screen.*/
    al_flip_display();

    /*
    Returns NULL if there was an error opening the window, or if text log windows are not implemented on the platform.
    dnf_log_window = al_open_native_text_log(
        "DNF Log", ALLEGRO_TEXTLOG_NO_CLOSE|ALLEGRO_TEXTLOG_MONOSPACE
    );
    if (dnf_log_window == NULL)
        dnf_abort("Failed to initialize native text log.");
    */

    if(!al_init_image_addon())
        dnf_abort("Failed to initialize al_init_image_addon.");

    if (init_resources())
        dnf_abort("Failed to initialize resources loader.");

    /* `al_create_event_queue` will return a new `ALLEGRO_EVENT_QUEUE` object. Should this function fail, it will return `NULL`. While failure is unlikely in this simple example, you are better off checking every single function that could fail for any errors. You may have fewer hidden problems when the program becomes more complicated. */
    manager->event_queue = al_create_event_queue();
    if(manager->event_queue == NULL)
        dnf_abort("Failed to create event_queue.");

    manager->run();

    /*
    TODO: file bug or research why atexit + allegro = segmentation faults
    probably thread-related...

    if (atexit(&dnf_shutdown))
        dnf_abort("failed to register exit function");
    */
    dnf_shutdown();
}


void dnf_shutdown(void) {
    dnf_alert("called");
    _dnf_free();
}

int main(void)
{
    DNF_LOG = fopen("dnf_log.txt","w"); // start log

    dnf_init();

    fclose(DNF_LOG); // end log

    return 0;
}
