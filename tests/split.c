#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "strsep.h"


int main(void)
{
    // More general pattern:
    const char *my_str_literal = "JAN{style}FEB{style}MAR";

    char *token, *str_pos, *str_start;

    str_start = str_pos = strdup(my_str_literal);
    while ((token = strsep(&str_pos, "{style}")))
    {
        if (!token || strcmp(token, "")){
            printf("%s\n", token);
        }
    }

    free(str_start);

    return 0;
}
