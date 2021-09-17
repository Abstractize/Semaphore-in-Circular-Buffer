#include <stdio.h>
#include "memory/memory.h"

#define BLOCK_SIZE 4096

int main()
{
    char *buffer_name = "buffer";
    if(create_memory_block(buffer_name, BLOCK_SIZE))
        printf("Created Block: %s\n", buffer_name);
    else
        printf("Couldn't create Block: %s\n", buffer_name);
    return 0;
}
