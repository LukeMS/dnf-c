#include "dnf.h"


Manager *manager = NULL;
//ALLEGRO_TEXTLOG* dnf_log_window = NULL;


void _dnf_free(void) {
    dnf_alert("called");

    if (manager->display != NULL)
        al_destroy_display(manager->display);
    if (manager->al_event_queue != NULL)
        al_destroy_event_queue(manager->al_event_queue);
    al_uninstall_system();

    unload_resources();
    del_Manager();
}

void dnf_parse_args(int argc, char const *argv[]) {
    dnf_info("cmdline args count=%d", argc);
     /* First argument is executable name only */
    for (int i=1; i < argc; i++) {
        //        dnf_info("\narg%d=%s", i, argv[i]);

        if (!(strcmp(argv[i], "NOINPUT"))) {
            // assign true to DNF_CMD_NOINPUT mask at manager->cmd_opt
            manager->cmd_opt |= DNF_CMD_NOINPUT;
        }

    }
}

void dnf_init(int argc, char const *argv[]) {
    dnf_alert("called");

    if (new_Manager())
        dnf_abort("failed to initialize 'manager'");

    dnf_parse_args(argc, argv);

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
    if(!al_init_font_addon())
        dnf_abort("Failed to initialize al_init_font_addon.");
    if(!al_init_ttf_addon())
        dnf_abort("Failed to initialize al_init_ttf_addon.");

    if (init_resources())
        dnf_abort("Failed to initialize resources loader.");

    /* `al_create_event_queue` will return a new `ALLEGRO_EVENT_QUEUE` object. Should this function fail, it will return `NULL`. While failure is unlikely in this simple example, you are better off checking every single function that could fail for any errors. You may have fewer hidden problems when the program becomes more complicated. */
    manager->al_event_queue = al_create_event_queue();
    if(manager->al_event_queue == NULL)
        dnf_abort("Failed to create al_event_queue.");

    /* Here we actually tie the display to the event queue so we can be informed of events from the display such as the close event. Without this function call, the display events will not be placed in this queue and thus will not be handled. */
    al_register_event_source(manager->al_event_queue,
                             al_get_display_event_source(manager->display));

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

int main(int argc, char const *argv[]) {
    DNF_LOG = fopen("dnf_log.txt","w"); // start log

    dnf_init(argc, argv);

    fclose(DNF_LOG); // end log

    return 0;
}
