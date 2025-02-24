/*
 * Operating Systems: Three Easy Pieces (OSTEP)
 *
 * Modified by Drue Coles. 
 *
 * A global variable is initialized to 0. One thread increments it k times 
 * and another thread decrements it k times, where k is specified by the 
 * user as a command-line argument. After both threads terminate, the 
 * program outputs the value of the global variable. 
 * 
 * Compile and link with -pthread option.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0; 

void *increment(void *); // increments counter 
void *decrement(void *); // decrements counter 

int main(int argc, char *argv[]) {
    // Extract number of increments/decrements from command line
    if (argc != 2) { 
	  printf("Usage: threads <reps>\n"); 
	  exit(1); 
    } 
    int n = atoi(argv[1]);
    
    pthread_t p1, p2;     
    pthread_create(&p1, NULL, increment, &n); 
    pthread_create(&p2, NULL, decrement, &n);
    
    // See what happens if these lines are omitted.
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("%d\n", counter);
    return 0;
}

void *increment(void *t) {    
    int n = *((int*) t);
    for (int i = 0; i < n; i++) {
	    counter++;
    }
    return NULL;
}

void *decrement(void *t) {
    int n = *((int*) t);
    for (int i = 0; i < n; i++) {
	    counter--;
    }
    return NULL;
}