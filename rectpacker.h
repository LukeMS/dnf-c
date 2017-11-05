#ifndef RECTPACKER_H
#define RECTPACKER_H


typedef struct DNF_rectpacker_Rect {
    int w;
    int h;
    int x;
    int y;
} DNF_rectpacker_Rect;

int DNF_rectpacker_imgpacker(int w, void* sources, int** max_h);

// 'namespace struct'
// ejrh.wordpress.com/2012/01/24/namespaces-in-c/
static const struct {
    int (* imgpacker)(int w, void* sources, int** max_h);
} rectpacker = {
    DNF_rectpacker_imgpacker  // rectpacker.imgpacker
};

#endif