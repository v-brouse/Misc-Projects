/*
 * Operating Systems: Three Easy Pieces (OSTEP)
 *
 * Modified and simplified by Drue Coles. 
 * 
 * Outputs PID and counter value 0-9 at one second intervals.
 *
 * To compile and run three instances of the program, enter:
 *
 *     $gcc -o cpu cpu.c
 *     $./cpu & ./cpu & ./cpu
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "common.h"

int main()
{
    pid_t pid = getpid();
    
    for (int i = 0; i < 10; i++) {
        printf("Process %d (count %d)\n", pid, i);
        spin(1);
    }
    return 0;
}