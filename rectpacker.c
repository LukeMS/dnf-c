#include <math.h>
#include <stdio.h>

#include "pqueue.h"
#include "zhash.h"

#include "rectpacker.h"


/*****************************************************************************
*                                                                            *
*  -------------------- DNF_rectpacker_decreasing_area---------------------  *
*                                                                            *
*****************************************************************************/
static int cmp_decreasing_area(const void *p1, const void *p2) {
    int v1 = ((DNF_rectpacker_Rect *) p1)->w * \
    		 ((DNF_rectpacker_Rect *) p1)->h;
    int v2 = ((DNF_rectpacker_Rect *) p2)->w * \
    		 ((DNF_rectpacker_Rect *) p2)->h;


    if (v1 > v2) return 1;
    if (v1 < v2) return -1;

    return 0;
}


int populate_queue(PQueue* queue, struct ZHashTable* sources) {

    TileSource*     src = NULL;

    dnf_info("sources->entry_count %d", sources->entry_count);

    for (struct ZHashEntry* p = sources->head; p; p = p->lnknext) {
        src = (TileSource*) p->val;
        src->img = al_load_bitmap(src->file);
        src->w   = al_get_bitmap_width(src->img);
        src->h   = al_get_bitmap_height(src->img);

        /*TODO:
        if using a single atlas instead of multiple images proves to be
        required, finish up rectangles packing and is logic
        */

        // al_destroy_bitmap(src->img);

        /*
        if ((pqueue_insert(queue, (const void*) src)))
            dnf_abort("pqueue_insert failure");
        */
    }

    return 0;
}

int DNF_rectpacker_imgpacker(int w, struct ZHashTable* sources, int* max_h) {
    int h = pow(2, 16);
    *max_h = -h;
    // DNF_rectpacker_Rect bin = {.w = w, .h = h};
    // dnf_alert("bin.w %d, bin.h %d", bin.w, bin.h);

    // PQueue* queue = calloc(1, sizeof(*queue));
    PQueue* queue = NULL;
    // pqueue_init(queue, &cmp_decreasing_area, NULL);

    populate_queue(queue, sources);

    // pqueue_destroy(queue);


    return 0;
}