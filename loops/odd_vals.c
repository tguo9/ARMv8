/* File:     odd_vals.c
 * Purpose:  Use ARMv8 assembly to write a function that initializes
 *           the n values in an array of long ints to 2i+1 for i = 0,
 *           1, ..., n-1.
 *
 * Compile:  gcc -g -Wall -o odd_vals odd_vals.c -DALL_C, or
 *           gcc -g -Wall -o odd_vals odd_vals.c odd_vals_func.s
 *
 * Run:      ./odd_vals
 * Input:    The long int n
 * Output:   The odd ints 1, 3, ..., 2*(n-1) + 1
 */
#include <stdio.h>
#include <stdlib.h>

void Assign_odds(long odd_vals[], long n);
void Print_array(char title[], long vals[], long n);

int main(void) {
   long n, *odd_vals;

   printf("How many odd values?\n");
   scanf("%ld", &n);
   odd_vals = malloc(n*sizeof(long));

   Assign_odds(odd_vals, n);

   Print_array("The values are", odd_vals, n);

   free(odd_vals);

   return 0;
}  /* main */

#ifdef ALL_C
/*---------------------------------------------------------------------
 * Function:  Assign_odds
 * Purpose:   Assign the values 1, 3, ..., 2(n-1)+1 to the n elements
 *            in the array odd_vals
 * In arg:    n
 * Out arg:   odd_vals
 */
void Assign_odds(long odd_vals[], long n) {
   long i;

   for (i = 0; i < n; i++)
      odd_vals[i] = 2*i + 1;
}  /* Assign_odds */ 
#endif


/*---------------------------------------------------------------------
 * Function:  Print_array
 * Purpose:   Print the long ints in an array with n elements
 * In args:   n, vals
 */
void Print_array(char title[], long vals[], long n) {
   long i;

   printf("%s:\n", title);
   for (i = 0; i < n; i++)
      printf("%ld ", vals[i]);
   printf("\n");
}  /* Print_array */
