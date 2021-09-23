#ifndef MEMORY_HEADER_H
#define MEMORY_HEADER_H

#include <stdbool.h>
#include "../data/datatypes.h"

initialization_data_t *attach_memory_info_block(char *name, int size);
data_t *attach_memory_data_block(char *name, int size, int buffer_size);
bool detach_memory_info_block(initialization_data_t *block);
bool detach_memory_data_block(data_t *block);

#endif