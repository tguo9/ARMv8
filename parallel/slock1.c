/* File:  
 *    slock1.c
 *
 * Purpose:
 *    Use a lock function created with ARM ldxr and stxr.  This
 *    version allows the user to execute many calls to the
 *    lock and unlock functions.
 *
 * Input:
 *    none
 * Output:
 *    message from thread after lock is acquired
 *
 * Compile:  
 *    gcc -g -Wall -o many many_iters.c lock.s unlock.s -lpthread
 * Usage:
 *    ./locks <thread_count> <iters>
 *
 * Note:
 *    Define ALL_C to use (broken) C spinlocks
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

/* Global variable:  accessible to all threads */
int thread_count;
int iters;
long lock = 0;
int total = 0;

void Usage(char* prog_name);
void *Thread_work(void* rank);  /* Thread function */

/* Assembly and C functions */
void Lock(long *lock_p, int one);
void Unlock(long *lock_p);

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 

   /* Get number of threads from command line */
   if (argc != 3) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);  
   iters = strtol(argv[2], NULL, 10);  
   if (thread_count <= 0) Usage(argv[0]);
   printf("Main > thread_count = %d, iters = %d, &lock = %p\n", 
         thread_count, iters, &lock);

   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          Thread_work, (void*) thread);  

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

   printf("total = %d\n", total);

   free(thread_handles);

   return 0;
}  /* main */


/*-------------------------------------------------------------------*/
void *Thread_work(void* rank) {
   int i;

   for (i = 0; i < iters; i++) {
      Lock(&lock, 1);
      total++;
      Unlock(&lock);
   }

   return NULL;
}  /* Thread_work */


/*-------------------------------------------------------------------*/
void Usage(char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads> <number of iters>\n", 
         prog_name);
   fprintf(stderr, "number of threads > 0\n");
   exit(0);
}  /* Usage */


#ifdef ALL_C
void Lock(long *lock_p, int one) {
   /* Wait for lock == 0 */
   while(lock == 1);

   /* Lock lock */
   lock = 1;
   return 0;
}  /* Lock */


void Unlock(long *lock_p) {
   lock = 0;
}  /* Unlock */
#endif
