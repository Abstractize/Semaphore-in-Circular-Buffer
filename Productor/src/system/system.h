/**
 * @file system.h
 * @author Gabriel Abarca Aguilar (gababarca@estudiantec.cr)
 * @brief System Overwrited Functions
 * @version 0.1
 * @date 2021-09-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * @brief Name of the Project
 * 
 */
extern const char *PROJECT_NAME;
/**
 * @brief Color the Console will display the name
 * 
 */
extern const char *COLOR_NAME_CONSOLE;
/**
 * @brief Color Black for the console
 * 
 */
extern const char *BLACK_CONSOLE;

/**
 * @brief Overwrited Print
 * 
 * @param string string to print
 */
void print(const char *string);
/**
 * @brief Overwrited print with a backslash
 * 
 * @param string string to print
 */
void println(const char *string);