//      File:       loop_func.s
//      Purpose:    Find the sum 1 + 2 + ... + n
//      Input args: x0 = n
//      Ret val:    1 + 2 + ... + n

//	The ``.global'' informs the linker that this code can
//         be called by code in other files
  	.global	Loop

//      n = x0, i = x10, sum = x11
//      What happens if we use the actual for loop test (i <= n)
Loop:
        mov     x10, 1        // i = 1
        mov     x11, 0        // sum = 0
        
Test:   subs    x9, x10, x0   // Subtract i - n to set 
                              //    condition codes
        b.le    Lp_bdy

        mov     x0, x11       // Ret val = sum = x11
        b       Done

Lp_bdy: add     x11, x11, x10 // x11 = sum += i = x9
        add     x10, x10, 1   // i++
        b       Test          // Go back to the start 
                              //    of the loop

Done:   br      lr

