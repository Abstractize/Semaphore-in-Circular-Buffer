#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory/memory.h"

#define BLOCK_SIZE 4096

int main(int argc, char *argv[])
{
    /*if (argc != 2)
    {
        printf("usage - %s [stuff to write]", argv[0]);
        return -1;
    }*/

    char *buffer_name = "buffer";
    char *block = attach_memory_block(buffer_name, BLOCK_SIZE);
    if (block == NULL)
    {
        printf("ERROR: couldn't get Block: %s\n", buffer_name);
        return -1;
    }

    char *to_write = "Hello World!";
    printf("Writing '%s'\n", to_write);
    strncpy(block, to_write, BLOCK_SIZE);

    detach_memory_block(block);

    return 0;
}
