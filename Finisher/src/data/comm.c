#include "comm.h"

int set_interface_attribs(int fd, int speed, int parity)
{
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0)
    {
        printf("Error tcgetattr In Port\n");
        return -1;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        printf("Error tcsetattr In Port\n");
        return -1;
    }
    return 0;
}

void set_blocking(int fd, int should_block)
{
    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(fd, &tty) != 0)
    {
        printf("Error tcgetattr In Port\n");
        return;
    }

    tty.c_cc[VMIN] = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
        printf("Error tcsetattr In Port\n");
}

void writePort(char *portname, int head, int tail)
{
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return;
    }

    set_interface_attribs(fd, B9600, 0);
    set_blocking(fd, 0);

    write(fd, (char)tail, 8);
    write(fd, (char)head, 8);
    close(fd);
}

void readPort(char *portname, initialization_data_t *info_block)
{
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return;
    }

    set_interface_attribs(fd, B9600, 0);
    set_blocking(fd, 0);

    char buf[100];
    int n = read(fd, &buf, sizeof(buf));
    if(n || strchr(buf, 's'))
        info_block->stop = true;
    close(fd);
}