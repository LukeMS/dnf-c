#include "scene_splash.h"

char* splash_path = "resources/gfx/DNF_splash1.png";
ALLEGRO_BITMAP* splash_img;


int DNF_scene_splash_load(DNF_Scene* scene, void* newdata) {
    splash_img = al_load_bitmap(splash_path);
    if(!(splash_img = al_load_bitmap(splash_path)))
        dnf_abort("Failed to load image!");

    return 0;
}

int DNF_scene_splash_update(DNF_Scene* scene) {

    return 0;

}

int DNF_scene_splash_draw(DNF_Scene* scene) {

    al_draw_bitmap(splash_img, 200, 200, 0);

    return 0;

}

int DNF_scene_splash_unload(DNF_Scene* scene) {

    return 0;

}