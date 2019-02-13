/* File:     loop.c
 * Purpose:  Read in a long int n, and compute the sum
 *
 *              1 + 2 + ... + n
 *
 * Compile:  gcc -g -Wall -o loop loop.c -DALL_C
 *              or
 *           gcc -g -Wall -o loop loop.c loop_func.s
 * Run:      ./loop
 *
 * Input:    A long int n
 * Output:   The sum 1 + 2 + ... + n
 */
#include <stdio.h>

/* This function does the addition        */
/* It can be implemented in C or Assembly */
long Loop(long n);

int main(void) {
   long n, sum;

   printf("Enter n\n");
   scanf("%ld", &n);

   sum = Loop(n);

   printf("The sum 1 + 2 + ... + %ld = %ld\n", n, sum); 

   return 0;
}  /* main */

#ifdef ALL_C
long Loop(long n) {
   long i, sum = 0;

   for (i = 1; i <= n; i++)
      sum += i;

   return sum;
}  /* Loop */
#endif
