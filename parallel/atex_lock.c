/* File:     atex_lock.c
 * Purpose:  Implement a spinlock using atomic exchange
 *
 * Compile:  gcc -g -Wall -o al atex_lock.c -lpthread
 * Run:      ./al <number of threads> <number of iterations>
 *
 * Algorithm:
 *    Main thread starts other threads
 *    Each thread executes iters iterations of lock acquisition,
 *       adding 1 to total, and relinquishing lock
 *    Main thread prints total
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>
#include <string.h>

#define UNLOCKED 0
#define LOCKED 1

/* Shared variables */
long total = 0;
long iters;
long thread_count;
// atomic_long is a special type in stdatomic.h
atomic_long spinlock = 0;  

void* Thread_work(void* rank);
void Lock(atomic_long* spinlock_p);
void Unlock(volatile atomic_long* spinlock_p);

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
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
            Thread_work, (void*) thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);

   printf("total = %ld\n", total);
   free(thread_handles);

   return 0;
}  /* main */


void* Thread_work(void* rank) {
// long my_rank = (long) rank;
   long i;

   for (i = 0; i < iters; i++) {
      Lock(&spinlock);
      total++;
      Unlock(&spinlock);
   }

   return NULL;
}  /* Thread_work */


void Lock(atomic_long* spinlock_p) {
   long ret_val;
   long value = LOCKED;

   do {
      ret_val = atomic_exchange(spinlock_p, value);
   } while (ret_val == LOCKED);
}  /* Lock */

void Unlock(volatile atomic_long* spinlock_p) {
   *spinlock_p = UNLOCKED;
}  /* Unlock */


