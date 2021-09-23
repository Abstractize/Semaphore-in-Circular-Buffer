#ifndef DATA_HEADER_H
#define DATA_HEADER_H

#include "datatypes.h"

int push_data(circular_buffer_t *c, int data, char *buffer_name);
int pop_data(circular_buffer_t *c, int *data, char *buffer_name);

#endif