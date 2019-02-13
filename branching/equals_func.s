//      File:       equals_func.s
//      Purpose:    Compare two long ints and determine whether they're
//                  equal. 
//      Input args: x0, x1, the two numbers being compared
//      Ret val:    x0, 1 if x0 = x1, else 0

//	The ``.global'' informs the linker that this code can
//         be called by code in other files
  	.global	Equals

Equals:
        sub     x9, x0, x1   // x9 = x0 - x1

        cbnz    x9, Not_eq   // Is x9 = 0?
        mov     x0, 1        // x9 = 0, so x0 = x1; rv = x0 = 1
        b       Done

Not_eq: mov     x0, 0        // x9 != 0, so x0 != x1; rv = x0 = 0

        // Return to the caller, return value in x0
	// ret
  Done: br      lr
