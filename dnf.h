#ifndef DNF_H
#define DNF_H

#define ALLEGRO_USE_CONSOLE 1

#ifdef _WIN32
#define DNF_OSPATHSEP '\\'
#else
#define DNF_OSPATHSEP '/'
#endif

/*
#ifdef DEBUG
#define DNF_DEBUG 1
#else
#define DNF_DEBUG 0
#endif
*/
/*
DNF_DEBUG verbosity level:
0 = off, no debugging functions/output;
1 = minor, small/essential information;
2 = medium, some info;
3 = full, beware of large outputs
*/
#define DNF_DEBUG 3

#include <stdio.h>
#include <stdint.h>

#include "dnfutil.h"
#include "manager.h"
#include "resources.h"

#include "zhash.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_native_dialog.h>

//ALLEGRO_TEXTLOG* dnf_log_window;
FILE * DNF_LOG;

void _dnf_free(void);

void dnf_init(void);

void dnf_shutdown(void);

#define dnf_abort(msg, ...) \
    do { \
        fprintf(stderr, "%s:%d  (%s)  ALERT: " msg "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        fprintf(DNF_LOG, "%s:%d  (%s)  ALERT: " msg "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        _dnf_free(); \
        exit(EXIT_FAILURE); \
    } while (0)

#define dnf_alert(msg, ...) \
    do { \
        if (DNF_DEBUG >= 2) { \
            fprintf(DNF_LOG, "%s:%d  (%s)  ALERT: " msg "\n", \
                    __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        } \
    } while (0)

#define dnf_info(msg, ...) \
    do { \
        if (DNF_DEBUG >= 3) { \
            fprintf(DNF_LOG, "%s:%d  (%s)  INFO: " msg "\n", \
                    __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        } \
    } while (0)

#endif
