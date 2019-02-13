/* File:     equals.c
 * Purpose:  Read in two long ints, and determine whether they're equal.
 *
 * Compile:  gcc -g -Wall -o equals equals.c -DALL_C
 *              or
 *           gcc -g -Wall -o equals equals.c equals.s
 * Run:      ./equals
 *
 * Input:    Two long ints
 * Output:   Whether they're equal.
 */
#include <stdio.h>

/* This function does the addition        */
/* It can be implemented in C or Assembly */
long Equals(long a, long b);

int main(void) {
   long a, b, result;

   printf("Enter a and b\n");
   scanf("%ld%ld", &a, &b);

   result = Equals(a, b);

   if (result == 1)
      printf("%ld = %ld\n", a, b);
   else 
      printf("%ld != %ld\n", a, b);

   return 0;
}  /* main */

#ifdef ALL_C
long Equals(long a, long b) {

   if (a == b)
      return 1;
   else 
      return 0;
}  /* Compare */
#endif
