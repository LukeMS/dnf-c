#ifndef RECTPACKER_H
#define RECTPACKER_H

#include "zhash.h"

#include "resources.h"


typedef struct DNF_rectpacker_Rect {
    int w;
    int h;
    int x;
    int y;
} DNF_rectpacker_Rect;

int DNF_rectpacker_imgpacker(int w, struct ZHashTable* sources, int* max_h);

// rectpacker 'namespace struct'
static const struct {
    int (* imgpacker)(int w, struct ZHashTable* sources, int* max_h);
} rectpacker = {
    DNF_rectpacker_imgpacker  // rectpacker.imgpacker
};

#endif