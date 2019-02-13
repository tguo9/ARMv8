/* File:     overflow.c
 * Purpose:  Look at what happens in a C program when there's been overflow.
 *
 * Compile:  gcc -g -Wall -o of overflow.c
 * Run:      ./of
 *
 * Input:    none
 * Output:   results of unsigned and signed operations that result
 *           in overflow.
 *
 * Note:     For 32 bit integer types the largest unsigned int is 
 *
 *                 2^32 - 1 = 0xffffffff
 *
 *           The largest positive signed int is
 *
 *                 2^31 - 1 = 0x7fffffff
 *
 *           The largest negative signed int (in absolute value) is
 *
 *                 -2^31 = 0x8000000
 */
#include <stdio.h>

int main(void) {
   unsigned max_u = 0xffffffff;  // Largest unsigned
   unsigned one_u = 0x1;
   unsigned zero_u = 0x0;
   unsigned result_u;

   int max_i = 0x7fffffff;  // Largest positive int
   int one_i = 0x1;
   int min_i = 0x80000000;  // Largest negative int (in absolute value)
   int result_i;

   printf("sizeof(unsigned) = %d\n", (int) sizeof(unsigned));
   result_u = max_u + one_u;
   printf("max_u + one_u = 0x%x = %u\n", result_u, result_u);
   result_u = zero_u - one_u;
   printf("zero_u - one_u = 0x%x = %u\n\n", result_u, result_u);

   printf("sizeof(int) = %d\n", (int) sizeof(int));
   result_i = max_i + one_i;
   printf("max_i + one_i = 0x%x = %d\n", result_i, result_i);
   result_i = min_i - one_i;
   printf("min_i - one_i = 0x%x = %d\n", result_i, result_i);

   return 0;
}
