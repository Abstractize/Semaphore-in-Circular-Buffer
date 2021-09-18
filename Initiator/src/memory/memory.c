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

#define IPC_RESULT_ERROR (-1)

static int get_shared_block(char *name, int size)
{
    key_t key = ftok(name, 0);
    printf("key: %i\n", key);
    if (key == IPC_RESULT_ERROR)
        return IPC_RESULT_ERROR;
    return shmget(key, size, 0664 | IPC_CREAT);
}

bool create_memory_block(char *name, int size)
{
    int fd2 = open(name, O_RDWR | O_CREAT, 0777);
    if (fd2 != -1)
        close(fd2);
    else
        return NULL;

    int shared_block_id = get_shared_block(name, size);
    if (shared_block_id == IPC_RESULT_ERROR)
        return NULL;
    return shared_block_id;
}
