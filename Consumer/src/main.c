#include <stdio.h>
#include <string.h>
#include "memory/memory.h"

#define BLOCK_SIZE 4096

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

   char *block = attach_memory_block(buffer_name, BLOCK_SIZE);
   if (block == NULL)
   {
      printf("ERROR: couldn't get Block: %s\n", buffer_name);
      return -1;
   }

   printf("Reading '%s'\n", block);

   detach_memory_block(block);
}