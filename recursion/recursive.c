/* File:     recursive.c
 * Purpose:  Read in a long int n, and compute the sum
 *
 *              1 + 2 + ... + n
 *
 *           using recursion.
 *
 * Compile:  gcc -g -Wall -o recur recursive.c -DALL_C
 *              or
 *           gcc -g -Wall -o recur recursive.c recursive_func.s
 * Run:      ./recur
 *
 * Input:    A long int n
 * Output:   The sum 1 + 2 + ... + n
 */
#include <stdio.h>

/* This function does the addition        */
/* It can be implemented in C or Assembly */
long Recur(long n);

int main(void) {
   long n, sum;

   printf("Enter n\n");
   scanf("%ld", &n);

   sum = Recur(n);

   printf("The sum 1 + 2 + ... + %ld = %ld\n", n, sum); 

   return 0;
}  /* main */

#ifdef ALL_C
long Recur(long n) {
   long sum;

   if (n == 1)
      return 1;
   else {
      sum = Recur(n-1);
      sum += n;
      return sum;
   }
}  /* Recur */
#endif
