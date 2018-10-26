#define VEC_CFG_IMPLEMENTATION
#include "str.h"

#include <string.h>

int str_cmp (struct str a, struct str b)
{
    return (a.ptr == b.ptr) ?
        0 :
        (a.length == b.length) ?
        strncmp(a.ptr, b.ptr, a.length) :
        (a.length < b.length) ?
        -1 :
        1 ;
}
