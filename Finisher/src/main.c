#include <stdio.h>
#include <string.h>
#include "memory/memory.h"

int main(int argc, char *argv[])
{
    char *buffer_name = NULL;
    for (int i = 0; i < argc; ++i)
        if (!strcmp(argv[i], "-n"))
            buffer_name = argv[++i];

    if (buffer_name == NULL)
    {
        printf("ERROR: couldn't get Block: %s\n", buffer_name);
        return -1;
    }

    if (destroy_memory_block(buffer_name))
        printf("Destroyed Block: %s\n", buffer_name);
    else
        printf("Couldn't destroy Block: %s\n", buffer_name);
    return 0;
}