/* File:     find_min.c
 * Purpose:  Find the subscript of the smallest value in a 
 *           subarray of long ints
 *
 * Compile:  gcc -g -Wall -o fm find_min.c  -DALL_C
 *              or
 *           gcc -g -Wall -o fm find_min.c find_min_func.s
 * Run:      ./fm <n> <min> <max> [modulus]
 *              n = number of elements in array
 *              min, max: subscripts, find the subscript of the smallest 
 *                 element arr[i],  where min <= i < max
 *              modulus: if present, the program will generate
 *                 the list using a random number generator,
 *                 and the array elements will be remainders
 *                 after division by modulus.  If not present,
 *                 the user will enter the elements of the array.
 *
 * Input:    If modulus is not present, the elements of the array
 * Output:   Subscript and value of the smallest element arr[i],
 *           where min <= i < max
 *
 * Notes:
 * 1.  The program assumes 0 <= min < max <= n
 * 2.  There is no error checking.
 */
#include <stdio.h>
#include <stdlib.h>

long Find_min(long arr[], long min, long max);

void Get_args(int argc, char* argv[], long* n_p, long* min_p,
      long* max_p, long* mod_p);
void Read_list(char prompt[], long arr[], long n);
void Gen_list(long arr[], long n, long modulus);
void Print_list(char title[], long arr[], long n);


int main(int argc, char* argv[]) {
   long n, min, max, modulus, minloc;
   long* arr;

   Get_args(argc, argv, &n, &min, &max, &modulus);
   arr = malloc(n*sizeof(long));
   /* modulus = 0 => user enters array elements */
   if (modulus == 0)
      Read_list("Enter the elements", arr, n);
   else
      Gen_list(arr, n, modulus);
   Print_list("The array", arr, n);

   minloc = Find_min(arr, min, max);

   printf("If %ld <= i < %ld, then the smallest element is %ld\n",
         min, max, arr[minloc]);
   printf("   and its subscript is %ld\n", minloc);

   free(arr);

   return 0;
}  /* main */


#ifdef ALL_C
/*---------------------------------------------------------------------
 * Function:  Find_min
 * Purpose:   Find the subscript i of the smallest element arr[i]
 *            where the subscript i satisfies min <= i < max 
 * Note:      Assumes 0 <= min < max <= number of elements in arr
 */
long Find_min(long arr[], long min, long max) {
   long i, minloc = min, minval = arr[min];

   for (i = min + 1; i < max; i++) 
      if (arr[i] < minval) {
         minloc = i;
         minval = arr[i];
      }

   return minloc;
}  /* Find_min */
#endif

/*---------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print info on how to run the program and quit
 */
void Usage(char progname[]) {
   fprintf(stderr, "usage:  %s <n> <min> <max> [modulus]\n", progname);
   fprintf(stderr, "   n = number of elements in array\n");
   fprintf(stderr, "   min, max: subscripts, find the subscript smallest \n");
   fprintf(stderr, "      element arr[i],  where min <= i < max\n");
   fprintf(stderr, "   modulus: if present, the program will generate\n");
   fprintf(stderr, "      the list using a random number generator,\n");
   fprintf(stderr, "      and the array elements will be remainders\n");
   fprintf(stderr, "      after division by modulus.  If not present,\n");
   fprintf(stderr, "      the user will enter the elements of the array.\n");
   exit(0);
}  /* Usage */


/*---------------------------------------------------------------------
 * Function:  Get_args
 * Purpose:   Get the command line arguments
 */
void Get_args(int argc, char* argv[], long* n_p, long* min_p,
      long* max_p, long* mod_p) {

   if (argc != 4 && argc != 5) Usage(argv[0]);
   *n_p = strtol(argv[1], NULL, 10);
   *min_p = strtol(argv[2], NULL, 10);
   *max_p = strtol(argv[3], NULL, 10);
   if (argc == 5)
      *mod_p = strtol(argv[4], NULL, 10);
   else
      *mod_p = 0;  /* 0 indicates, user will enter data */
}  /* Get_args */


/*---------------------------------------------------------------------
 * Function:  Read_list
 * Purpose:   Read the contents of an array of long ints from stdin
 */
void Read_list(char prompt[], long arr[], long n) {
   long i;

   printf("%s:\n", prompt);
   for (i = 0; i < n; i++)
      scanf("%ld", &arr[i]);
}  /* Read_list */


/*---------------------------------------------------------------------
 * Function:  Gen_list
 * Purpose:   Generate the contents of an array of long ints using
 *            the C-library random random number generator.  Actual
 *            array elements are the remainder of a random value
 *            divided by modulus
 */
void Gen_list(long arr[], long n, long modulus) {
   long i;

   srandom(1);
   for (i = 0; i < n; i++)
      arr[i] = random() % modulus;
}  /* Gen_list */


/*---------------------------------------------------------------------
 * Function:  Print_list
 * Purpose:   Print the contents of an array of long ints to stdout
 */
void Print_list(char title[], long arr[], long n) {
   long i;

   printf("%s:\n", title); 
   for (i = 0; i < n; i++)
      printf("%ld ", arr[i]);
   printf("\n");
}  /* Print_list */
