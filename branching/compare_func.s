//      File:       compare_func.s
//      Purpose:    Compare two long ints and determine whether the
//                  the first is greater than, less than, or equal
//                  to the seconc
//      Input args: x0, x1, the two numbers being compared
//      Ret val:    x0, -1 if x0 < x1, 0 if x0 = x1, +1 if x0 > x1

//	The ``.global'' informs the linker that this code can
//         be called by code in other files
  	.global	Compare

Compare:
        // Subtract x0 - x1 and set the condition codes
        subs    x9, x0, x1
        b.lt Less
        b.eq Equal

        mov   x0, 1    // x0 > x1
        b Done

Less:   mov   x0, -1   // x0 < x1
        b Done 

Equal:  mov   x0, xzr  // x0 = x1

        // Return to the caller, return value in x0
	// ret
Done:   br      lr
