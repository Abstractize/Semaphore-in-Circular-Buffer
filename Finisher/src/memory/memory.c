#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../data/datatypes.h"

#define IPC_RESULT_ERROR (-1)

static int get_shared_block(char *name, int size)
{
    key_t key;
    key = ftok(name, 0);
    if (key == IPC_RESULT_ERROR)
        return IPC_RESULT_ERROR;
    return shmget(key, size, 0664 | IPC_CREAT);
}

static int get_shared_data_block(char *name, int size, int num)
{
    key_t key = ftok(name, num);
    if (key == IPC_RESULT_ERROR)
        return IPC_RESULT_ERROR;
    return shmget(key, size, 0664 | IPC_CREAT);
}

initialization_data_t *attach_memory_info_block(char *name, int size)
{
    int shared_block_id = get_shared_block(name, size);
    initialization_data_t *result = malloc(size);

    if (shared_block_id == IPC_RESULT_ERROR)
        return NULL;

    result = (initialization_data_t *)shmat(shared_block_id, NULL, 0);
    if (result == (initialization_data_t *)IPC_RESULT_ERROR)
        return NULL;

    return result;
}

data_t *attach_memory_data_block(char *name, int size, int num)
{
    int shared_block_id = get_shared_data_block(name, size, num);
    data_t *result = malloc(size);

    if (shared_block_id == IPC_RESULT_ERROR)
        return NULL;

    result = (data_t *)shmat(shared_block_id, NULL, 0);
    if (result == (data_t *)IPC_RESULT_ERROR)
        return NULL;

    return result;
}

bool detach_memory_info_block(initialization_data_t *block)
{
    return (shmdt(block) != IPC_RESULT_ERROR);
}

bool detach_memory_data_block(data_t *block)
{
    return (shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_memory_block(char *name)
{
    int shared_blocked_id = get_shared_block(name, 0);

    if(shared_blocked_id == IPC_RESULT_ERROR)
        return NULL;

    bool result = (shmctl(shared_blocked_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
    result = result && (remove(name) == 0);

    return result;
}