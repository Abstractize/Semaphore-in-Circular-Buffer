#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "memory/memory.h"
#include "data/datatypes.h"
#include "data/data.h"

#define INFO_BLOCK_SIZE sizeof(initialization_data_t)
#define DATA_BLOCK_SIZE sizeof(data_t)

int main(int argc, char *argv[])
{
    char *buffer_name = NULL;
    int size = 0;

    for (int i = 0; i < argc; ++i)
        if (!strcmp(argv[i], "-n"))
            buffer_name = argv[++i];
        else if (!strcmp(argv[i], "-s"))
            size = atoi(argv[++i]);

    if (buffer_name == NULL || size < 1)
    {
        printf("Couldn't create Block: %s\n", buffer_name);
        return -1;
    }

    if (create_memory_block(buffer_name, INFO_BLOCK_SIZE))
        printf("Created Block: %s\n", buffer_name);
    else
    {
        printf("Couldn't create Block: %s\n", buffer_name);
        return -1;
    }

    initialization_data_t data = {
        .size = size,
        .buffer = {
            .head = 0,
            .tail = 0,
            .maxlen = size + 1},
        .consumers = 0,
        .productors = 0
    };

    strcpy(data.name, buffer_name);

    initialization_data_t *data_ptr = &data;
    initialization_data_t *info_block = attach_memory_info_block(buffer_name, INFO_BLOCK_SIZE);

    if (info_block == NULL)
    {
        printf("ERROR: couldn't get Block: %s\n", buffer_name);
        return -1;
    }
        
    memcpy(info_block, data_ptr, INFO_BLOCK_SIZE);

    sem_init(&info_block->sems.circular_buffer_usage_sem, 1, 1);
    sem_init(&info_block->sems.circular_buffer_full, 1, 1);
    sem_init(&info_block->sems.circular_buffer_empty, 1, 1);

    sem_wait(&info_block->sems.circular_buffer_empty);

    detach_memory_info_block(info_block);

    return 0;
}
