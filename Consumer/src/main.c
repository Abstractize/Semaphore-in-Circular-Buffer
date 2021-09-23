#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "memory/memory.h"
#include "data/datatypes.h"
#include "data/data.h"

#define BLOCK_SIZE sizeof(initialization_data_t)

int main(int argc, char *argv[])
{
   char *buffer_name = NULL;
   int prod_time = 0;
   for (int i = 0; i < argc; ++i)
      if (!strcmp(argv[i], "-n"))
         buffer_name = argv[++i];
      else if (!strcmp(argv[i], "-t"))
         prod_time = atoi(argv[++i]);

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

   const int p_id = getpid();
   printf("Got %s in PID %i and instance Consumer %i\n", info_block->name, p_id, instance_id);

   int key = 8;
   double lambda = 1 / prod_time;

   while (key != (p_id % 6))
   {
      int lower_limit = lambda / 2 * 10000;
      int greater_limit = lambda * 10000;

      int random_prob = (rand() % (lower_limit + greater_limit) + 1);
      double x = (double)random_prob / 10000;
      x = x * prod_time;
      double t = -log(x) * prod_time;

      sleep(t);
      data_t *var = pop_data(&info_block->buffer, buffer_name, info_block->sems);
      if (var != NULL)
         print_data(var, "Consumer", instance_id, t);
      else
         printf("Could not POP value\n");
      key = var->key;
   }

   --info_block->consumers;
   detach_memory_info_block(info_block);

   return 0;
}