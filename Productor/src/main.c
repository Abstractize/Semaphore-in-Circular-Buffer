#include <stdio.h>
#include <string.h>
#include <time.h>
#include "memory/memory.h"
#include "data/datatypes.h"
#include "data/data.h"

#define INFO_BLOCK_SIZE sizeof(initialization_data_t)

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

    initialization_data_t *info_block = attach_memory_info_block(buffer_name, INFO_BLOCK_SIZE);
    if (info_block == NULL)
    {
        printf("ERROR: couldn't get Block: %s\n", buffer_name);
        return -1;
    }

    int instance_id = ++info_block->productors;
    
    printf("Got %s\n", info_block->name);
    for (int i = 0; i < info_block->size; ++i)
    {
        data_t value = {
            .index = i,
            .current_time = time(NULL),
            .consumers = info_block->consumers,
            .productors = info_block->productors,
            .data = ((i + 1) * 5)
        };
        
        data_t *response = push_data(&info_block->buffer, value, buffer_name, info_block->sems);
        if (response == NULL)
            printf("Error: 'NPI'\n");
        else
            print_data(response, "Productor", instance_id);
    }
    --info_block->productors;
    detach_memory_info_block(info_block);

    return 0;
}
