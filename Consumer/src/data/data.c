#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "datatypes.h"
#include "../memory/memory.h"

#define DATA_BLOCK_SIZE sizeof(data_t)

data_t *push_data(circular_buffer_t *c, data_t data, char *buffer_name, buffer_sems_t sems)
{
    sem_wait(&sems.circular_buffer_usage_sem);
    int next = c->head + 1;

    const bool is_gt_size = next >= c->maxlen;
    if (is_gt_size)
        next = 0;

    const bool is_full = next == c->tail;
    if (is_full)
        return NULL;

    int i = c->head;
    data_t *buffer_val = attach_memory_data_block(buffer_name, DATA_BLOCK_SIZE, i + 1);
    if (buffer_val == NULL)
        return NULL;

    *buffer_val = data;
    c->head = next;
    data_t *response = (data_t *)malloc(sizeof(data_t)); 
    *response = *buffer_val;
    detach_memory_data_block(buffer_val);
    sem_post(&sems.circular_buffer_usage_sem);
    return response;
}

data_t *pop_data(circular_buffer_t *c, char *buffer_name, buffer_sems_t sems)
{
    sem_wait(&sems.circular_buffer_usage_sem);
    const bool is_empty = c->head == c->tail;
    if (is_empty)
        return NULL;

    int next = c->tail + 1;
    const bool is_gt_size = next >= c->maxlen;
    if (is_gt_size)
        next = 0;

    int i = c->tail;
    data_t *buffer_val = attach_memory_data_block(buffer_name, DATA_BLOCK_SIZE, i + 1);
    data_t *data = (data_t *)malloc(sizeof(data_t)); 
    *data = *buffer_val;
    
    c->tail = next;
    detach_memory_data_block(buffer_val);

    sem_post(&sems.circular_buffer_usage_sem);
    return data;
}