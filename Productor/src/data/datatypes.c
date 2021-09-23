#include <stdio.h>
#include <time.h>
#include "datatypes.h"

void print_data(data_t * data, char * instance_name, int instance_id, double t)
{
    printf("\n");
    printf("--------------------------------------\n");
    printf("%s %i on index: %i\n", instance_name, instance_id, data->index);
    printf("Message Emited Date: %s", ctime(&data->current_time));
    printf("Message: %i\n", data->data);
    printf("Number of Consumers: %i\n", data->consumers);
    printf("Number of Productors: %i\n", data->productors);
    printf("Waited: %lf seconds\n", t);
    printf("--------------------------------------\n");
    printf("\n");
}