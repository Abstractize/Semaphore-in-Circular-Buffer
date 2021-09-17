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
    if(key == IPC_RESULT_ERROR)
        return IPC_RESULT_ERROR;
    return shmget(key, size, 0664 |  IPC_CREAT);
}

bool destroy_memory_block(char *name)
{
    int shared_blocked_id = get_shared_block(name, 0);

    if(shared_blocked_id == IPC_RESULT_ERROR)
        return NULL;
    return (shmctl(shared_blocked_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}