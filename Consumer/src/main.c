#include <stdio.h>
#include <string.h>
#include "memory/memory.h"
#include "data/datatypes.h"
#include "data/data.h"

#define BLOCK_SIZE sizeof(initialization_data_t)

int main(int argc, char *argv[])
{
   char *buffer_name = NULL;
   for (int i = 0; i < argc; ++i)
      if (!strcmp(argv[i], "-n"))
         buffer_name = argv[++i];

   if (buffer_name == NULL)
   {
      printf("ERROR: couldn't get Block: %s\n", buffer_name);
      return -1;
   }

   initialization_data_t *info_block = attach_memory_info_block(buffer_name, BLOCK_SIZE);
   if (info_block == NULL)
   {
      printf("ERROR: couldn't get Block: %s\n", buffer_name);
      return -1;
   }
   int instance_id = ++info_block->consumers;

   printf("Got %s\n", info_block->name);
   for (int i = 0; i < info_block->size; ++i)
   {
      data_t *var = pop_data(&info_block->buffer, buffer_name, info_block->sems);
      if (var == NULL)
         printf("value %i: not popped\n", i);
      else
         print_data(var, "Consumer", instance_id);
   }
   --info_block->consumers;
   detach_memory_info_block(info_block);

   return 0;
}