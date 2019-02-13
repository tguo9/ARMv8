/* File:     race_cond.c
 * Purpose:  Try to keep a running sum with multiple
 *           threads adding into a shared variable.
 *
 * Compile:  gcc -g -Wall o rc race_cond.c -lpthread 
 * Run:      ./rc <number of threads> <number of iterations>
 *
 * Algorithm:
 *    Main thread starts other threads
 *    Each thread executes iters iterations adding 1 into
 *       total in each iteration.
 *    Main thread prints total
 *
 * Note:    There are definite problems with the C implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/* Shared variables */
long total = 0;
long iters;
long thread_count;

void* Thread_work(void* rank);

int main(int argc, char* argv[]) {
   long thread;
   pthread_t *thread_handles;

   if (argc != 3) {
      fprintf(stderr, "usage: %s <number of threads> <iterations>\n", 
            argv[0]);
      exit(0);
   }
   thread_count = strtol(argv[1], NULL, 10);
   iters = strtol(argv[2], NULL, 10);

   thread_handles = malloc(thread_count*sizeof(pthread_t));

   /* Start threads */
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
            Thread_work, (void*) thread);

   /* Join threads */
   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);

   printf("Total = %ld\n", total);
   free(thread_handles);

   return 0;
}  /* main */


void* Thread_work(void* rank) {
   long i;

   for (i = 0; i < iters; i++) {
      total++;
   }

   return NULL;
}  /* Thread_work */




