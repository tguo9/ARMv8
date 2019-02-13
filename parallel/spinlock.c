/* File:     spinlock.c
 * Purpose:  Try to implement a spinlock using C, and 
 *           implement a spinlock using x86 assembly
 *
 * Compile:  gcc -g -Wall -DALL_C -o spinlock spinlock.c  \
 *                 -lpthread  # C
 *           gcc -g -Wall -o spinlock spinlock.c spin.s  \
 *                 -lpthread  # x86 
 * Run:      ./spinlock <number of threads> <number of iterations>
 *
 * Algorithm:
 *    Main thread starts other threads
 *    Each thread executes iters iterations of acquiring the
 *       lock, adding 1 to a running total and relinquishing
 *       the lock
 *    Main thread prints total
 *
 * Note:    There are definite problems with the C implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define UNLOCKED 0
#define LOCKED 1

/* Shared variables */
long total = 0;
long iters;
long thread_count;
long spinlock = UNLOCKED;

void* Thread_work(void* rank);
void Lock(long* spinlock_p);
void Unlock(long* spinlock_p);

int main(int argc, char* argv[]) {
   long thread;
   pthread_t *thread_handles;

   if (argc != 3) {
      fprintf(stderr, "usage: %s <number of threads> <iterations>\n", argv[0]);
      exit(0);
   }
   thread_count = strtol(argv[1], NULL, 10);
   iters = strtol(argv[2], NULL, 10);

   thread_handles = malloc(thread_count*sizeof(pthread_t));
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
            Thread_work, (void*) thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);

   printf("Total = %ld\n", total);
   free(thread_handles);

   return 0;
}  /* main */


void* Thread_work(void* rank) {
   long i;

   for (i = 0; i < iters; i++) {
      Lock(&spinlock);
      total++;
      Unlock(&spinlock);
   }

   return NULL;
}  /* Thread_work */


#ifdef ALL_C
void Lock(long* spinlock_p) {
   while(*spinlock_p == LOCKED);
   *spinlock_p = LOCKED;
}  /* Lock */

void Unlock(long* spinlock_p) {
   *spinlock_p = UNLOCKED;
}  /* Unlock */
#endif


