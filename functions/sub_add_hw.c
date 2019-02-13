/* File:     sub_add_hw.c
 * Purpose:  Read in three long ints, a, b, and c.  Compute a-b 
 *           (a-b) + c using a single function whose inputs are
 *           the addresses of a, b, and c, and whose return value
 *           is a-b+c.
 *
 * Compile:  gcc -g -Wall -o sub_add sub_add_hw.c -DALL_C
 *              or
 *           gcc -g -Wall -o sub_add_hw sub_add_hw.c sub_add_hw_func.s
 * Run:      ./sub_add_hw
 *
 * Input:    Three long ints a, b, c
 * Output:   (a - b) + c
 */
#include <stdio.h>

/* This function does the subtraction and the addition */
/* It can be implemented in C or Assembly              */
long Sub_add(long* a_p, long* b_p, long* c_p);


int main(void) {
   long a, b, c, diff_sum;

   printf("Enter a, b, and c\n");
   scanf("%ld%ld%ld", &a, &b, &c);

   diff_sum = Sub_add(&a, &b, &c);

   printf("a - b + c = %ld - %ld + %ld = %ld\n", a, b, c, diff_sum);

   return 0;
}  /* main */

#ifdef ALL_C
long Sub_add(long* a_p, long* b_p, long* c_p) {
   long diff_sum;

   diff_sum = *a_p - *b_p + *c_p ;
   return diff_sum;
}  /* Sub_add */
#endif
