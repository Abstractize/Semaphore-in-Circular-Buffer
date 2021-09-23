#ifndef DATA_TYPE_HEADER_H
#define DATA_TYPE_HEADER_H

#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>
#define BIG_ENOUGH 255

typedef struct
{
    int data;
} data_t;

typedef struct
{
    int head;
    int tail;
    int maxlen;
} circular_buffer_t;


typedef struct
{
    sem_t circular_buffer_usage_sem;
    sem_t circular_buffer_full;
} buffer_sems_t;
typedef struct
{
    char name[BIG_ENOUGH];
    buffer_sems_t sems;
    int size;
    int consumers;
    int productors;
    int time_prom;
    circular_buffer_t buffer;
} initialization_data_t;

#endif