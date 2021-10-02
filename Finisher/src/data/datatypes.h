#ifndef DATA_TYPE_HEADER_H
#define DATA_TYPE_HEADER_H

#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>
#include <time.h>

#define BIG_ENOUGH 255

typedef struct
{
    int key;
    int index;
    time_t current_time;
    int consumers;
    int productors;
    int productor_id;
    int data;
} data_t;

/**
 * @brief prints block data
 * 
 * @param data 
 * @param instance_name 
 * @param instance_id 
 * @param t 
 */
void print_data(data_t * data, char * instance_name, int instance_id, double t);

typedef struct
{
    int head;
    int tail;
    int maxlen;
} circular_buffer_t;

typedef struct
{
    int messages;
    double wait_time;
    double stop_time;
    double total_time;
} stats_t;

/**
 * @brief print stats
 * 
 * @param stats 
 * @param instance_name 
 * @param instance_id 
 */
void print_stats(stats_t stats, char * instance_name, int instance_id);

typedef struct
{
    sem_t circular_buffer_usage_sem;
    sem_t circular_buffer_full;
    sem_t circular_buffer_empty;
} buffer_sems_t;

typedef struct
{
    char name[BIG_ENOUGH];
    buffer_sems_t sems;
    int size;
    int consumers;
    int productors;
    circular_buffer_t buffer;
    bool stop;
} initialization_data_t;

#endif