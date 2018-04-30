#include "rope.h"

int main (void)
{
    struct rope * r = rope_new();
    rope_push(r, str_new());
    r = rope_free(r);

    return 0;
}
