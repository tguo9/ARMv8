/* File:     compare.c
 * Purpose:  Read in two long ints, and determine whether the
 *           first is > the second, equal to the second, or
 *           < the second
 *
 * Compile:  gcc -g -Wall -o compare compare.c -DALL_C
 *              or
 *           gcc -g -Wall -o compare compare.c compare_func.s
 * Run:      ./compare
 *
 * Input:    Two long ints
 * Output:   Whether the first is > second, less than the second,
 *           or equal to the second
 */
#include <stdio.h>

/* This function does the addition        */
/* It can be implemented in C or Assembly */
long Compare(long a, long b);

int main(void) {
   long a, b, result;

   printf("Enter a and b\n");
   scanf("%ld%ld", &a, &b);

   result = Compare(a, b);

   if (result == 1)
      printf("%ld > %ld\n", a, b);
   else if (result == -1)
      printf("%ld < %ld\n", a, b);
   else
      printf("%ld = %ld\n", a, b);

   return 0;
}  /* main */

#ifdef ALL_C
long Compare(long a, long b) {

   if (a > b)
      return 1;
   else if (a < b)
      return -1;
   else // a = b
      return 0;
}  /* Compare */
#endif
