#include <stdbool.h>
#include "../data/datatypes.h"

#define BLOCK_SIZE 4096

initialization_data_t *attach_memory_info_block(char *name, int size);
bool detach_memory_info_block(initialization_data_t *block);
bool destroy_memory_block(char *name);