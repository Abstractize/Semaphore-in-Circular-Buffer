#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "datatypes.h"

/**
 * @brief Set the interface attribs object
 * 
 * @param fd 
 * @param speed 
 * @param parity 
 * @return -1 in case of error, 0 in case of success 
 */
int set_interface_attribs(int fd, int speed, int parity);
/**
 * @brief Set the port blocking
 * 
 * @param fd 
 * @param should_block 
 */
void set_blocking(int fd, int should_block);
/**
 * @brief writes the head and tail of circular buffer to serial
 * 
 * @param portname 
 * @param head 
 * @param tail 
 */
void writePort(char *portname, int head, int tail);
/**
 * @brief read message from serial
 * 
 * @param portname 
 * @param info_block 
 */
void readPort(char *portname, initialization_data_t *info_block);