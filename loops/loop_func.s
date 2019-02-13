//      File:       loop_func.s
//      Purpose:    Find the sum 1 + 2 + ... + n
//      Input args: x0 = n
//      Ret val:    1 + 2 + ... + n

//	The ``.global'' informs the linker that this code can
//         be called by code in other files
  	.global	Loop

Loop:
        mov     x10, 1        // i = 1
        mov     x11, 0        // sum = 0
        
Test:  
        subs    x9, x10, x0   // Subtract i - x0 to set the condition codes
        b.gt Done
        
        add     x11, x11, x10 // x11 = sum += i = x10
        add     x10, x10, 1   // i++
        b       Test          // Go back to the beginning of the loop

Done:   mov     x0, x11       // Return value = sum = x11

        // Return to the caller, return value in x0
	// ret
        br      lr
