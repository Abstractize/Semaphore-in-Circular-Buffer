#ifndef DATA_HEADER_H
#define DATA_HEADER_H

#include "datatypes.h"

/**
 * @brief Push data block to the shared array
 * 
 * @param c 
 * @param data 
 * @param buffer_name 
 * @param sems 
 * @param stats 
 * @return data_t* 
 */
data_t *push_data(circular_buffer_t *c, data_t data, char *buffer_name, buffer_sems_t *sems, stats_t *stats);
/**
 * @brief Pops data block from shared array
 * 
 * @param c 
 * @param buffer_name 
 * @param sems 
 * @param stats 
 * @return data_t* 
 */
data_t *pop_data(circular_buffer_t *c, char *buffer_name, buffer_sems_t *sems, stats_t *stats);

#endif