#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "datatypes.h"
#include "../memory/memory.h"

#define DATA_BLOCK_SIZE sizeof(data_t)

static bool full(circular_buffer_t *c)
{
    int next_push = c->head + 1;

    const bool is_gt_size = next_push > c->maxlen - 1;
    if (is_gt_size)
        next_push = 0;

    return next_push == c->tail;
}

static bool empty(circular_buffer_t *c)
{
    return c->head == c->tail;
}

data_t *push_data(circular_buffer_t *c, data_t data, char *buffer_name, buffer_sems_t *sems)
{
    const bool was_empty = empty(c);
    const bool is_full = full(c);
    
    if (is_full)
        sem_wait(&sems->circular_buffer_full);

    sem_wait(&sems->circular_buffer_usage_sem);

    int next = c->head + 1;
    
    const bool is_gt_size = next > c->maxlen;
    if (is_gt_size)
        next = 0;

    int i = c->head;
    data.index = i;
    data_t *buffer_val = attach_memory_data_block(buffer_name, DATA_BLOCK_SIZE, i + 1);
    if (buffer_val == NULL)
        return NULL;

    *buffer_val = data;
    c->head = next;
    data_t *response = (data_t *)malloc(sizeof(data_t));
    *response = *buffer_val;
    detach_memory_data_block(buffer_val);

    sem_post(&sems->circular_buffer_usage_sem);

    if (full(c))
        sem_wait(&sems->circular_buffer_full);
    if(was_empty)
        sem_post(&sems->circular_buffer_empty);
    
    return response;
}

data_t *pop_data(circular_buffer_t *c, char *buffer_name, buffer_sems_t *sems)
{
    const bool was_full = full(c);
    const bool is_empty = empty(c);

    if (is_empty)
        sem_wait(&sems->circular_buffer_empty);

    sem_wait(&sems->circular_buffer_usage_sem);

    int next = c->tail + 1;
    const bool is_gt_size = next > c->maxlen;
    if (is_gt_size)
        next = 0;

    int i = c->tail;
    data_t *buffer_val = attach_memory_data_block(buffer_name, DATA_BLOCK_SIZE, i + 1);

    data_t *data = (data_t *)malloc(sizeof(data_t));
    *data = *buffer_val;

    c->tail = next;
    detach_memory_data_block(buffer_val);

    sem_post(&sems->circular_buffer_usage_sem);
    
    if (empty(c))
        sem_wait(&sems->circular_buffer_empty);

    if(was_full)
        sem_post(&sems->circular_buffer_full);

    return data;
}