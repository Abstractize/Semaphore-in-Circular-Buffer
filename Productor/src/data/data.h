#ifndef DATA_HEADER_H
#define DATA_HEADER_H

#include "datatypes.h"

data_t *push_data(circular_buffer_t *c, data_t data, char *buffer_name);
data_t *pop_data(circular_buffer_t *c, char *buffer_name);

#endif