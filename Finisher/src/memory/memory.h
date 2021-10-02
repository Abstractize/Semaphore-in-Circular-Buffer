#ifndef MEMORY_HEADER_H
#define MEMORY_HEADER_H

#include <stdbool.h>
#include "../data/datatypes.h"

/**
 * @brief attaches info block to shared emmory
 * 
 * @param name 
 * @param size 
 * @return initialization_data_t* 
 */
initialization_data_t *attach_memory_info_block(char *name, int size);

/**
 * @brief attaches memory block to shared emmory
 * 
 * @param name 
 * @param size 
 * @param buffer_size 
 * @return data_t* 
 */
data_t *attach_memory_data_block(char *name, int size, int buffer_size);

/**
 * @brief deattaches info block to shared emmory
 * 
 * @param block 
 * @return true 
 * @return false 
 */
bool detach_memory_info_block(initialization_data_t *block);

/**
 * @brief deattaches memory block to shared emmory
 * 
 * @param block 
 * @return true 
 * @return false 
 */
bool detach_memory_data_block(data_t *block);

/**
 * @brief Destroys memory block from shared memory
 * 
 * @param name 
 * @return true 
 * @return false 
 */
bool destroy_memory_block(char *name);

#endif