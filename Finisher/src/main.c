#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include "memory/memory.h"
#include "data/datatypes.h"

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

    initialization_data_t *info_block = attach_memory_info_block(buffer_name, BLOCK_SIZE);
    
    sem_destroy(&info_block->sems.circular_buffer_usage_sem);
    
    detach_memory_info_block(info_block);

    if (destroy_memory_block(buffer_name))
        printf("Destroyed Block: %s\n", buffer_name);
    else
        printf("Couldn't destroy Block: %s\n", buffer_name);
    return 0;
}