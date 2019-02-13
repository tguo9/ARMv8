/* File:     count_sort.c
 * Purpose:  Implement count sort in C and ARMv8
 *
 * Compile:  gcc -g -Wall -o ct_sort count_sort.c -DALL_C
 *              or
 *           gcc -g -Wall -o ct_sort count_sort.c count_sort_func.s
 * Run:      ./ct_sort <n> [modulus]
 *              n:  number of long ints to be sorted
 *              modulus:  if present, generate a list of
 *                  random long ints using the C random
 *                  function.  The values in the list are
 *                  the remainders after division by 
 *                  modulus.  If modulus is absent, the
 *                  user will enter the lists from
 *                  stdin.
 *
 * Input:    See "Run" above.
 * Output:   The sorted list.
 *
 * Note:     The temporary array is statically allocated.  So n <= 100
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

void Usage(const char progname[]);
void Read_list(const char prompt[], long list[], long n);
void Gen_list(long list[], long n, long modulus);
void Print_list(const char title[], long list[], long n);

void Count_sort(long list[], long n);
long Count_lt(long list[], long n, long i);
void Copy_list(long outlist[], long inlist[], long n);

int main(int argc, char* argv[]) {
   long n, *list, modulus = 0;

   if (argc != 2 && argc != 3) Usage(argv[0]);
   n = strtol(argv[1], NULL, 10);
   if (argc == 3)
      modulus = strtol(argv[2], NULL, 10);

   list = malloc(n*sizeof(long));
   if (modulus == 0)
      Read_list("Enter the elements", list, n);
   else
      Gen_list(list, n, modulus);
   Print_list("Before sort", list, n);

   Count_sort(list, n);

   Print_list("After sort", list, n);

   free(list);
   return 0;
}  /* main */


#ifdef ALL_C
/*---------------------------------------------------------------------
 * Function:    Count_sort
 * Purpose:     Sort a list of long ints using count sort
 * In arg:      n:  number of elements in list
 * In/out arg:  list
 *
 * Note:        The temporary array temp is statically allocated
 *              with MAX_N elements.  So n should be <= MAX_N.
 *              This is not checked.
 */
void Count_sort(long list[], long n) {
   long i, j;
   long temp[MAX_N];

   for (i = 0; i < n; i++) {
      j = Count_lt(list, n, i);
      temp[j] = list[i];
   }

   Copy_list(list, temp, n);
}  /* Count_sort */


/*---------------------------------------------------------------------
 * Function:    Count_lt
 * Purpose:     Find the number of elements in the list that are
 *                 < list[i]
 * In args:     list, n, i 
 * Ret val:     number of elements less than list[i]
 *
 * Note:        If list[i] = list[j], then list[j] is counted
 *                 as less than list[i] if j < i
 */
long Count_lt(long list[], long n, long i) {
   long j, less_than = 0;

   for (j = 0; j < n; j++)
      if (list[j] < list[i])
         less_than++;
      else if (list[i] == list[j] && j < i)
         less_than++;
   return less_than;
}  /* Count_lt */


/*---------------------------------------------------------------------
 * Function:    Copy_list
 * Purpose:     Copy the contents of one list into another
 * In args:     inlist, n
 * Out arg:     outlist
 */
void Copy_list(long outlist[], long inlist[], long n) {
   long i;

   for (i = 0; i < n; i++)
      outlist[i] = inlist[i];
}  /* Copy_list */
#endif

/*---------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print how the program should be started and quit
 * In arg:    progname
 */
void Usage(const char progname[]) {
   fprintf(stderr, "%s <n> [modulus]\n", progname); 
   fprintf(stderr, "   n:  number of long ints to be sorted\n");
   fprintf(stderr, "   modulus:  if present, generate a list of\n");
   fprintf(stderr, "      random long ints using the C random\n");
   fprintf(stderr, "      function.  The values in the list are\n");
   fprintf(stderr, "      the remainders after division by\n");
   fprintf(stderr, "      modulus.  If modulus is absent, the\n");
   fprintf(stderr, "      user will enter the lists from stdin.\n");
   exit(0);
}  /* Usage */

/*---------------------------------------------------------------------
 * Function:  Read_list
 * Purpose:   Read in a list of long ints from stdin
 * In args:   prompt:
 *            n:  number of elements in list
 * Out arg:   list
 */
void Read_list(const char prompt[], long list[], long n) {
   int i;
   printf("%s\n", prompt);
   for (i = 0; i < n; i++)
      scanf("%ld", &list[i]);
}  /* Read_list */


/*---------------------------------------------------------------------
 * Function:   Gen_list
 * Purpose:    Use the C random random number generator to generate a 
 *                list of long ints
 * In args:    n:  number of elements in the list
 *             modulus:  random numbers are divided by modulus and
 *                the remainder is the value inserted in the list            
 * Out arg:    list
 */
void Gen_list(long list[], long n, long modulus)  {
   int i;

   srandom(1);
   for (i = 0; i < n; i++)
      list[i] = random() % modulus;
}  /* Gen_list */


/*---------------------------------------------------------------------
 * Function:   Print_list
 * Purpose:    Print the contents of a list of long ints
 * In args:    title:
 *             n:  number of elements in the list
 *             list
 */
void Print_list(const char title[], long list[], long n) {
   int i;

   printf("%s:\n", title);
   for (i = 0; i < n; i++)
      printf("%ld ", list[i]);
   printf("\n");
}  /* Print_list */
