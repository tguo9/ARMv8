//      File:  fibo_recur_func.s

//      Function:  Gen_fibo
//      Purpose:   Compute the nth Fibonacci number
//      In arg:    n = x0
//      Ret val:   f_n = x0, the nth Fibonacci number
        .global Gen_fibo

//      x0 = x20 = n,   x19 = f_n_minus_2,
Gen_fibo:
        sub     sp, sp, 32      // Add storage for 4 long words
                                //    Only need 3
        stur    lr, [sp, 16]    // Push return address
        stur    x19, [sp, 8]    // Push x19
        stur    x20, [sp, 0]    // Push x20

        cbnz    x0, N_gt_0      // x0 > 0, go to N_gt_0

        mov     x0, 0           // Set ret val to 0
        b       Done

N_gt_0: sub     x9, x0, 1       // Is n = 1?
        cbnz    x9, N_gt_1      // If not, go to N_gt_1

        mov     x0, 1           // Set ret val to 1
        b       Done

N_gt_1: mov     x20, x0         // Put n in a save register
        sub     x0, x0, 2       // n = n - 2
        bl      Gen_fibo        // Compute f_n_minus_2

        mov     x19, x0         // f_n_minus_2 = x0
        sub     x0, x20, 1      // n = n - 1
        bl      Gen_fibo        // Compute f_n_minus_1
        
        add     x0, x0, x19     // f_n = f_n_minus_1 + f_n_minus_2

  Done: ldur    lr, [sp, 16]    // Restore lr from stack
        ldur    x19, [sp, 8]    // Restore x19 from stack
        ldur    x20, [sp, 0]    // Restore x20 from stack
        add     sp, sp, 32      // Reset stack pointer
        br      lr
