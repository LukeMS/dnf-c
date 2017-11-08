#include "scene_splash.h"

char           *splash_path = "resources/gfx/DNF_splash1.png";
char           *font_path   = "resources/fonts/pirulen.ttf";
ALLEGRO_BITMAP *splash_img;
ALLEGRO_FONT   *font;

typedef struct SceneSplashData {
    float alpha;
    int direction;
    int img_done;
} SceneSplashData;


DNF_Scene* DNF_scene_splash_init(void) {
    DNF_Scene *scene;
    scene = DNF_scene_base_init(); /* 'super' */

    scene->load   = DNF_scene_splash_load;
    scene->update = DNF_scene_splash_update;
    scene->draw   = DNF_scene_splash_draw;
    scene->unload = DNF_scene_splash_unload;
    scene->data   = calloc(1, sizeof(SceneSplashData));
    ((SceneSplashData *)scene->data)->direction = 1;

    return scene;
}

int DNF_scene_splash_load(DNF_Scene* scene, void* newdata) {
    splash_img = al_load_bitmap(splash_path);
    if(!(splash_img = al_load_bitmap(splash_path)))
        dnf_abort("Failed to load image!");

    if(!(font = al_load_ttf_font(font_path, 18, 0)))
        dnf_abort("Failed to load font!");

    manager->events->watch(manager->events, "UPDATE", scene->update);
    manager->events->watch(manager->events, "DRAW",   scene->draw);

    return 0;
}

int DNF_scene_splash_update(void* scene_evt) {
    DNF_Scene *scene = ((DNF_SceneEvt*) scene_evt)->scene;
    SceneSplashData *data = scene->data;
    if (!data->img_done) {
        // increasing opacity
        if (data->direction == 1) {
            if (data->alpha >= 1.0) {
                data->alpha = 1.0;
                data->direction = -1;
            } else {
                data->alpha += 0.1;
            }
        // decreasing opacity
        } else if (data->direction == -1) {
            if (data->alpha <= 0.0) {
                data->alpha = 0.0;
                data->direction = 1;
                data->img_done = 1;
            } else {
                data->alpha -= 0.1;
            }
        }
    } else {
        ; // next image or next scene
    }


    return 0;

}

int DNF_scene_splash_draw(void* scene_evt) {
    DNF_Scene *scene = ((DNF_SceneEvt*) scene_evt)->scene;
    SceneSplashData *data = scene->data;

    al_draw_textf(font, al_map_rgb(255, 255, 255), 54, 8,
                  ALLEGRO_ALIGN_LEFT, "ALPHA: %f", data->alpha);

    al_draw_tinted_bitmap(
        splash_img,
        al_map_rgba_f(1.0*data->alpha,
                      1.0*data->alpha,
                      1.0*data->alpha,
                      data->alpha),
                      100, 100, 0);
    /*
    al_draw_bitmap(splash_img, 200, 200, 0);
    The above will draw the bitmap 50% transparently.
    Like al_draw_bitmap but multiplies all colors in the bitmap with the given color.
    */

    return 0;

}

int DNF_scene_splash_unload(DNF_Scene* scene) {

    return 0;

}