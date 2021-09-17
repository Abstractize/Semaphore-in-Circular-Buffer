#include <stdbool.h>

#define BLOCK_SIZE 4096

char *attach_memory_block(char *name, int size);
char *detach_memory_block(char *name);