#include "scene_base.h"

DNF_Scene* DNF_scene_base_init(void) {
    DNF_Scene *new;
    if (!(new = calloc(1, sizeof(*new))))
        dnf_abort("Failed to allocate memory for scene.");

    return new;
}