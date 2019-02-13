/* File:     sub_add.c
 * Purpose:  Read in three long ints, a, b, and c.  Compute a-b and
 *           (a-b) + c using a Subtraction function and an Add function.
 *           Print the results
 *
 * Compile:  gcc -g -Wall -o sub_add sub_add.c -DALL_C
 *              or
 *           gcc -g -Wall -o sub_add sub_add.c sub_add_func.s
 * Run:      ./sub_add
 *
 * Input:    Three long ints a, b, c
 * Output:   a - b and (a - b) + c
 */
#include <stdio.h>

/* This function does the subtraction and the addition */
/* It can be implemented in C or Assembly              */
void Sub_add(long a, long b, long c, long* diff_p, long* diff_sum_p);

/* This function does the addition        */
/* It can be implemented in C or Assembly */
long Add(long x, long y);

int main(void) {
   long a, b, c, diff, diff_sum;

   printf("Enter a, b, and c\n");
   scanf("%ld%ld%ld", &a, &b, &c);

   Sub_add(a, b, c, &diff, &diff_sum);

   printf("a - b = %ld - %ld = %ld\n", a, b, diff);
   printf("a - b + c = %ld - %ld + %ld = %ld\n", a, b, c, diff_sum);

   return 0;
}  /* main */

#ifdef ALL_C
void Sub_add(long a, long b, long c, long* diff_p, long* diff_sum_p) {

   *diff_p = a - b;
   *diff_sum_p = Add(*diff_p, c);
}  /* Sub_add */

long Add(long x, long y) {
   long z;

   z = x + y;
   return z;
}  /* Add */
#endif
