#include "dnfutil.h"


uint32_t fmtime(const char* filename)
{
    if(stat(filename, &fmtime_result)==0)
    {
        return fmtime_result.st_mtime;

    }

   return 0;
}

const char* get_file_ext(const char* fspec) {
    char *e = strrchr (fspec, '.');
    if (e == NULL) {
        e = ""; // fast method, could also use &(fspec[strlen(fspec)]).
    } else {
        ++e;
    }
    return e;
}



