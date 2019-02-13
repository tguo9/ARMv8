/* File:     fibo_recur.c
 * Purpose:  Compute the first n Fibonacci numbers.  This version
 *           uses recursion.
 *
 * Compile:  gcc -g -Wall -o fibo fibo_recur.c -DALL_C
 * Run:      ./fibo
 *
 * Input:    n:  the number of Fibonacci numbers to compute
 * Output:   f_0, f_1, ..., f_n-1
 */
#include <stdio.h>
#include <stdlib.h>

long Gen_fibo(long n);

int main(void) {
   long i, n;

   printf("How many Fibonacci numbers?\n");
   scanf("%ld", &n);

   printf("The first %ld Fibonacci numbers are:\n", n);
   for (i = 0; i < n; i++)
      printf("%ld ", Gen_fibo(i));
   printf("\n");

   return 0;
}  /* main */

#ifdef ALL_C
long Gen_fibo(long n) {
   long f_n, f_n_minus_1, f_n_minus_2;

   if (n == 0)
      return 0;
   else if (n == 1)
      return 1;
   else {
      f_n_minus_2 = Gen_fibo(n-2);
      f_n_minus_1 = Gen_fibo(n-1);
      f_n = f_n_minus_1 + f_n_minus_2;
      return f_n;
   }
}  /* Gen_fibo */
#endif
