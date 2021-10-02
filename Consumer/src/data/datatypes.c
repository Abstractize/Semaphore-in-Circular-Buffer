#include <stdio.h>
#include <time.h>
#include "datatypes.h"

void print_data(data_t * data, char * instance_name, int instance_id, double t)
{
    printf("\n");
    printf("\033[0;32m");
    printf("--------------------------------------\n");
    printf("%s %i on index: %i\n", instance_name, instance_id, data->index + 1);
    printf("Message Emited Date: %s", ctime(&data->current_time));
    printf("Message: %i\n", data->data);
    printf("Number of Consumers: %i\n", data->consumers);
    printf("Number of Productors: %i\n", data->productors);
    printf("Waited: %lf seconds\n", t);
    printf("--------------------------------------\n");
    printf("\033[0m");
    printf("\n");
}

void print_stats(stats_t stats, char * instance_name, int instance_id)
{
    printf("\n");
    printf("\033[0;34m");
    printf("--------------------------------------\n");
    printf("%s %i Stats\n", instance_name, instance_id);
    printf("Messages Consumed: %i\n",stats.messages);
    printf("Total Wait Time: %lf\n", stats.wait_time);
    printf("Total Semaphore wait time: %lf\n", stats.stop_time);
    printf("Kernel time: %lf\n", stats.total_time);
    printf("--------------------------------------\n");
    printf("\033[0m");
    printf("\n");
}