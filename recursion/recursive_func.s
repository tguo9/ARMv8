//      File:       recursive_func.s
//      Purpose:    Find the sum 1 + 2 + ... + n using recursion
//      Input args: x0 = n
//      Ret val:    1 + 2 + ... + n

  	.global	Recur

//      x0 = n when called,  x19 = n after return from call
//      ret val = x0
Recur:
        sub     sp, sp, 16    // Saving two long words on stack
        stur    lr, [sp, 8]   // Push lr onto stack
        stur    x19, [sp, 0]  // Push callee-save register x19

        sub     x9, x0, 1     // Subtract so we can check 
                              //   n != 1
        
Test:  
        cbnz    x9, Rec_call  // x0 != 1, Make a recursive call

        mov     x0, 1         // Base case, n = 1, return 1
        b       Done          // Go to Done

Rec_call:
        mov     x19, x0       // x19 = x0 = n for this call
        sub     x0, x0, 1     // x0 for next call = n-1
        bl      Recur         // Call Recur(n-1)
        add     x0, x0, x19   // new ret val = x0 = old ret val + x19
                              //                  = x0 + n


Done:   ldur    x19, [sp, 0]  // Restore callee-saved value
        ldur    lr, [sp, 8]   // Restore return address
        add     sp, sp, 16    // Reset stack pointer
        br      lr
