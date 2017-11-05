#ifndef DNFUTIL_H
#define DNFUTIL_H

//required by fmtime
#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>

#include <allegro5/allegro.h>

//required by fmtime
// -lmingw32 will be required
#ifdef WIN32
#define stat _stat
#endif


// How to check the last modified time of a file
// stackoverflow.com/a/40504396/5496529
struct stat fmtime_result;
uint32_t fmtime(const char* filename);


const char* get_file_ext(const char* fspec);


#endif
