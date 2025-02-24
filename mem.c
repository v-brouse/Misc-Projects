/*
 * Operating Systems: Three Easy Pieces (OSTEP)
 *
 * Modified and simplified by Drue Coles. 
 * 
 * Allocates memory for an int and assigns a counter value (0-9)
 * at one second intervals.
 *
 * To compile and run three instances of the program, enter:
 *
 *     $gcc -o mem mem.c
 *     $./mem & ./mem & ./mem
 *
 * To make the intended point about memory virtualization, ASLR must be disabled.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "common.h"

int main() {
    int *ptr = malloc(sizeof(int));
    pid_t pid = getpid();
    printf("Process %d: allocated memory at %p\n\n", pid, ptr);
    spin(1);
    for (int i = 0; i < 5; i++) {
        (*ptr)++;
        printf("Process %d: incrementing value at %p (%d)\n", pid, ptr, *ptr);
        spin(1);
    }
    return 0;
}