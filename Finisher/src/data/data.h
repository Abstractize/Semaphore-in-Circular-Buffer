#ifndef DATA_HEADER_H
#define DATA_HEADER_H

#include "datatypes.h"

int push_data(circular_buffer_t *c, int data, char *buffer_name, buffer_sems_t sems);
int pop_data(circular_buffer_t *c, int *data, char *buffer_name, buffer_sems_t sems);

#endif