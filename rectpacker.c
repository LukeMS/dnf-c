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

    for (struct ZHashEntry* p = sources->head; p; p = p->lnknext) {
        // (?cast? *) p->val);
    }
}

int DNF_rectpacker_imgpacker(int w, void* sources, int** max_h) {
    int h = pow(2, 16);
    **max_h = -h;
    DNF_rectpacker_Rect bin = {.w = w, .h = h};
    // printf("bin.w %d, bin.h %d\n", bin.w, bin.h);

    PQueue queue;
    pqueue_init(&queue, &cmp_decreasing_area, NULL);

    populate_queue(&queue, sources);




    return 0;
}