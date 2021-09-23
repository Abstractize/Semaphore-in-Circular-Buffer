#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "datatypes.h"
#include "../memory/memory.h"

#define DATA_BLOCK_SIZE sizeof(data_t)

int push_data(circular_buffer_t *c, int data, char *buffer_name, buffer_sems_t sems)
{
    sem_wait(&sems.circular_buffer_usage_sem);
    
    int next = c->head + 1;

    const bool is_gt_size = next >= c->maxlen;
    if (is_gt_size)
        next = 0;

    const bool is_full = next == c->tail;
    if (is_full)
        return -1;

    int i = c->head;
    data_t *buffer_val = attach_memory_data_block(buffer_name, DATA_BLOCK_SIZE, i + 1);
    if(buffer_val == NULL)
        return -1;
    buffer_val->data = data;
    c->head = next;
    detach_memory_data_block(buffer_val);
        
    sem_post(&sems.circular_buffer_usage_sem);
    return 0;
}

int pop_data(circular_buffer_t *c, int *data, char *buffer_name)
{

    sem_wait(&sems.circular_buffer_usage_sem);

    const bool is_empty = c->head == c->tail;
    if (is_empty)
        return -1;

    int next = c->tail + 1;
    const bool is_gt_size = next >= c->maxlen;
    if (is_gt_size)
        next = 0;

    int i = c->tail;
    data_t *buffer_val = attach_memory_data_block(buffer_name, DATA_BLOCK_SIZE, i + 1);
    if(buffer_val == NULL)
        return -1;
    *data = buffer_val->data;
    c->tail = next;
    detach_memory_data_block(buffer_val);

    sem_post(&sems.circular_buffer_usage_sem);
    return 0;
}