/* File:     add2.c
 * Purpose:  Read in two long ints, add them and print the result
 *           This version passes pointers to the input values
 *
 * Compile:  gcc -g -Wall -o add1 add1.c -DALL_C
 *              or
 *           gcc -g -Wall -o add1 add1.c add1_func.s
 * Run:      ./add
 *
 * Input:    Two long ints
 * Output:   Their sum
 */
#include <stdio.h>

/* This function does the addition        */
/* It can be implemented in C or Assembly */
void Add(long* a_p, long* b_p, long* c_p );

int main(void) {
   long a, b, c;

   printf("Enter a and b\n");
   scanf("%ld%ld", &a, &b);

   Add(&a, &b, &c);

   printf("a + b = %ld + %ld = %ld = c\n", a, b, c);

   return 0;
}  /* main */

#ifdef ALL_C
void Add(long* a_p, long* b_p, long* c_p) {

   *c_p = *a_p + *b_p;
   return;
}  /* Add */
#endif
