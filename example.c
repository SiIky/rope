#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils/ifjmp.h>

#include "rope.h"
#include "str.h"

void str_print (const struct str s)
{
    printf("%s", str_as_slice(&s));
}

int usage (const char * cmd)
{
    fprintf(stderr,
            "Usage: %s FILE...\n",
            cmd);
    return !0;
}

#define BUF_SIZE 4096

int main (int argc, char ** argv)
{
    if (argc < 2)
        return usage(*argv);

    FILE * fin = NULL;
    char l[BUF_SIZE] = "";

    struct rope _r = {0};
    struct rope * r = &_r;

    for (int i = 1; i < argc; i++) {
        fin = fopen(argv[i], "r");
        if (fin == NULL)
            continue;

        while (fgets(l, BUF_SIZE, fin)) {
            char * ptr = calloc(BUF_SIZE, sizeof(char));
            if (ptr == NULL)
                continue;

            size_t capacity = strlen(l) + 1;
            size_t length = capacity;

            struct str s = {0};
            str_from_raw_parts(&s, ptr, length, capacity);

            strncpy(ptr, l, length);

            rope_push(r, s);
        }

        fclose(fin);

        rope_foreach(r, str_print);

        rope_truncate(r, 0);
    }

    _r = rope_free(_r);

    return 0;
}
