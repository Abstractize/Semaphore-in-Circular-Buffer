#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdbool.h>
#include "memory/memory.h"
#include "data/datatypes.h"
#include "data/comm.h"

#define BLOCK_SIZE sizeof(initialization_data_t)

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
    // Arduino Com

    // While not pressed
    // If has data sends data to led
    // If Button was pressed
    initialization_data_t *info_block = attach_memory_info_block(buffer_name, BLOCK_SIZE);
    if (info_block == NULL)
    {
        printf("ERROR: couldn't get Block: %s\n", buffer_name);
        return -1;
    }

    info_block->stop = true;

    printf("\n");
    printf("--------------------------------------\n");
    printf("Message On buffer: %s", abs(info_block->buffer.head - info_block->buffer.head));
    printf("--------------------------------------\n");
    printf("\n");

    sem_destroy(&info_block->sems.circular_buffer_usage_sem);
    sem_destroy(&info_block->sems.circular_buffer_empty);
    sem_destroy(&info_block->sems.circular_buffer_full);

    detach_memory_info_block(info_block);

    if (destroy_memory_block(buffer_name)){
        printf("Destroyed Block: %s\n", buffer_name);
    }
        
    else
        printf("Couldn't destroy Block: %s\n", buffer_name);
    return 0;
}