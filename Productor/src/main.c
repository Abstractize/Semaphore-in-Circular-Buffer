#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "memory/memory.h"
#include "data/datatypes.h"
#include "data/data.h"

#define INFO_BLOCK_SIZE sizeof(initialization_data_t)

int main(int argc, char *argv[])
{
    char *buffer_name = NULL;
    int prod_time = 0;
    for (int i = 0; i < argc; ++i)
        if (!strcmp(argv[i], "-n"))
            buffer_name = argv[++i];
        else if (!strcmp(argv[i], "-t"))
            prod_time = atoi(argv[++i]);

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

    printf("Got %s in PID %i and instance Productor %i\n", info_block->name, getpid(), instance_id);

    int mn_value = 0;
    while (!info_block->stop)
    {
        int random_prob = ((rand() % (10000/prod_time)) + 1);
        double x  = (double) random_prob/10000;
        x = x * prod_time;
        double t = -log(x) * prod_time;
        
        sleep(t);

        const int magic_number = mn_value % 6;

        data_t value = {
            .key = magic_number,
            .current_time = time(NULL),
            .consumers = info_block->consumers,
            .productors = info_block->productors,
            .productor_id = instance_id,
            .data = rand() % 32767};

        data_t *response = push_data(&info_block->buffer, value, buffer_name, info_block->sems);
        if(response != NULL)
            print_data(response, "Productor", instance_id, t);
        else
            break;
        mn_value++;
    }

    --info_block->productors;
    detach_memory_info_block(info_block);

    return 0;
}
