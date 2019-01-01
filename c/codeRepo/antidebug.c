#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include"antidebug.h"


int pid_sid(void)
{
    if (getsid(getpid()) != getppid()) {
        exit(EXIT_FAILURE);
    }
    return 0;
}