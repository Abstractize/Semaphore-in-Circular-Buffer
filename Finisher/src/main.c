#include <stdio.h>
#include "memory/memory.h"

int main(int argc, char *argv[])
{
    /*if (argc != 1)
    {
        printf("usage - %s (no args)", argv[0]);
    }*/

    char *buffer_name = "buffer";

    if (destroy_memory_block(buffer_name))
        printf("Destroyed Block: %s\n", buffer_name);
    else
        printf("Couldn't destroy Block: %s\n", buffer_name);
    return 0;
}