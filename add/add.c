/* File:     add.c
 * Purpose:  Read in two long ints, add them and print the result
 *
 * Compile:  gcc -g -Wall -o add add.c -DALL_C
 *              or
 *           gcc -g -Wall -o add add.c add_func.s
 * Run:      ./add
 *
 * Input:    Two long ints
 * Output:   Their sum
 */
#include <stdio.h>

/* This function does the addition        */
/* It can be implemented in C or Assembly */
long Add(long a, long b);

int main(void) {
   long a, b, c;

   printf("Enter a and b\n");
   scanf("%ld%ld", &a, &b);

   c = Add(a, b);

   printf("a + b = %ld + %ld = %ld = c\n", a, b, c);

   return 0;
}  /* main */

#ifdef ALL_C
long Add(long a, long b) {
   long c;

   c = a + b;
   return c;
}  /* Add */
#endif
