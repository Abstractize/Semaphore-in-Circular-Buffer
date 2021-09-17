#include <stdio.h>
#include <string.h>
#include "memory/memory.h"

#define BLOCK_SIZE 4096

int main(int argc, char *argv[])
{
   /*if(argc != 1)
   {
      printf("usage - %s //no args", argv[0]);
      return -1;
   }*/
   char *buffer_name = "buffer";
   char *block = attach_memory_block(buffer_name, BLOCK_SIZE);
   if (block == NULL)
   {
      printf("ERROR: couldn't get Block: %s\n", buffer_name);
      return -1;
   }

   printf("Reading '%s'", block);

   detach_memory_block(block);
}