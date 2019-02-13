//      File:       add_func.s
//      Purpose:    Implement addition of two long ints in ARMv8
//      Input args: x0, x1, the two numbers being added
//      Ret val:    x0, the sum of the two input values

//	The ``.global'' informs the linker that this code can
//         be called by code in other files
  	.global	Add

Add:
        // Add the contents of registers x0 and x1, storing the
        // result in x0
	add	x0, x1, x0

        // Return to the caller, return value in x0
	// ret
        br      lr
