#include "scene_splash.h"

char* splash_path = "resources/gfx/dnf_logo.png";
ALLEGRO_BITMAP* splash_img;


int DNF_scene_splash_load(DNF_Scene* scene, void* newdata) {
    splash_img = al_load_bitmap(splash_path);

    return 0;
}

int DNF_scene_splash_update(DNF_Scene* scene) {

    return 0;

}