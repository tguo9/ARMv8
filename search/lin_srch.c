/* File:     lin_srch.c
 * Purpose:  Use recursion to carry out a linear search
 *           on a user input unsorted list of long ints.
 *
 * Compile:  gcc -g -Wall -o lsrch lin_srch.c -DALL_C or
 *           gcc -g -Wall -o lsrch lin_srch.c lin_srch_func.s
 * Run:      ./lsrch
 *
 * Input:    n:  number of elements in list
 *           The elements of the list 
 *           The value to search for
 * Output:   Whether the value is in the list.
 */
#include <stdio.h>
#include <stdlib.h>

long Lin_srch(long list[], long n, long val, long curr);
void Print_list(long list[], long n);
void Read_list(long list[], long n);

int main(void) {
   long *list, n, loc, val;

   printf("Enter the number of elements in the list\n");
   scanf("%ld", &n);
   list = malloc(n*sizeof(long));
   printf("Enter the elements of the list\n");
   Read_list(list, n);
   printf("We read\n");
   Print_list(list, n);
   printf("Enter the value to search for\n");
   scanf("%ld", &val);

   loc = Lin_srch(list, n, val, 0);

   if (loc >= 0)
      printf("We found %ld in slot %ld\n",
         val, loc);
   else
      printf("%ld is not in the list\n",
         val);

   free(list);
   return 0;
}

#ifdef ALL_C
long Lin_srch(long list[], long n, long val, long curr) {
   long result;

   if (curr == n)
      result = -1;
   else if (list[curr] == val)
      return curr;
   else {
      curr++;
      result = Lin_srch(list, n, val, curr);
   }

   return result;
}  /* Lin_srch */
#endif


void Read_list(long list[], long n) {
   int i;
   for (i = 0; i < n; i++)
      scanf("%ld", &list[i]);
}  /* Read_list */


void Print_list(long list[], long n) {
   int i;
   for (i = 0; i < n; i++)
      printf("%ld ", list[i]);
   printf("\n");
}  /* Print_list */
