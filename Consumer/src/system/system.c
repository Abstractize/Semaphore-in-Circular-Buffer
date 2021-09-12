#include <stdio.h>
#include <time.h>
#include <string.h>

const char *PROJECT_NAME = "Consumer";
const char *COLOR_NAME_CONSOLE = "\033[0;35m";
const char *BLACK_CONSOLE = "\033[0;37m";

void print(const char *string)
{
    time_t t;
    time(&t);
    char * now = ctime(&t);
    now[strlen(now)-1] = '\0';

    printf("%s", COLOR_NAME_CONSOLE);
    printf("[%s: %s]: ", now, PROJECT_NAME);
    printf("%s", BLACK_CONSOLE);
    printf(": %s", string);
}

void println(const char *string)
{
    time_t t;
    time(&t);
    char * now = ctime(&t);
    now[strlen(now)-1] = '\0';

    printf("%s", COLOR_NAME_CONSOLE);
    printf("[%s: %s]: ", now, PROJECT_NAME);
    printf("%s", BLACK_CONSOLE);
    printf("%s\n", string);
}