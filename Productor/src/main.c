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

    if (buffer_name == NULL || prod_time <= 0)
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
    double lambda = 1 / (double)prod_time;

    printf("Got %s in PID %i and instance Productor %i\n", info_block->name, getpid(), instance_id);

    stats_t stats_block = {
            .messages = 0,
            .wait_time = 0,
            .stop_time = 0,
            .total_time = 0};
    
    clock_t begin_run = clock();

    while (!info_block->stop)
    {
        int lower_limit = lambda / 2 * 10000;
        int greater_limit = lambda * 10000;

        int random_prob = (rand() % (greater_limit - lower_limit) + 1) + lower_limit;

        double x = (double)random_prob / 10000;
        x = x * prod_time;
        double t = -log(x) * prod_time;

        sleep(t);
        stats_block.wait_time += t;

        const int posibilities = 6;
        const int magic_number = random() % (posibilities + 1);

        data_t value = {
            .key = magic_number,
            .current_time = time(NULL),
            .consumers = info_block->consumers,
            .productors = info_block->productors,
            .productor_id = instance_id,
            .data = rand() % 32767};

        data_t *response = push_data(&info_block->buffer, value, buffer_name, &info_block->sems, &stats_block);
        if (response != NULL){
            print_data(response, "Productor", instance_id, t);
            stats_block.messages++;
        }
        else
            break;
    }
    clock_t end_run = clock();

    stats_block.total_time += (double)(end_run - begin_run);

    --info_block->productors;
    detach_memory_info_block(info_block);

    print_stats(stats_block, "Productor", instance_id);

    return 0;
}
