#ifndef DNF_H
#define DNF_H

#include <stdio.h>
#include <stdint.h>

#include "dnfutil.h"
#include "manager.h"
#include "resources.h"

#include "zhash.h"

#include <allegro5/allegro.h>

void _dnf_free(void);
void dnf_init(void);
void dnf_shutdown(void);
#define dnf_abort(msg) \
    do \
    { \
        fprintf(stderr, "%s:%8d (%s) ERROR: %s\n", \
                __FILE__, __LINE__, __func__, msg); \
        _dnf_free(); \
        exit(EXIT_FAILURE); \
    } while (0)

#endif
