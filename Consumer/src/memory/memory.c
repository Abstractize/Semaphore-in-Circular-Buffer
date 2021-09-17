#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define IPC_RESULT_ERROR (-1)

static int get_shared_block(char *name, int size)
{
    key_t key;
    key = ftok(name, 0);
    if (key == IPC_RESULT_ERROR)
        return IPC_RESULT_ERROR;
    return shmget(key, size, 0664 | IPC_CREAT);
}

char *attach_memory_block(char *name, int size)
{
    int shared_block_id = get_shared_block(name, size);
    char *result;

    if (shared_block_id == IPC_RESULT_ERROR)
        return NULL;

    result = shmat(shared_block_id, NULL, 0);
    if (result == (char *)IPC_RESULT_ERROR)
        return NULL;

    return result;
}

bool detach_memory_block(char *block) 
{
    return (shmdt(block) != IPC_RESULT_ERROR);
}
