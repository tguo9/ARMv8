//      File:  fibo_iter_func.s

//      Function:  Gen_fibo
//      Purpose:   Generate the first n Fibonacci numbers and
//                 store them in an array.  This version uses 
//                 iteration.
//      In arg:    x1 = n
//      Out arg:   x0 = fibo[] array for the first n Fibonacci
//                 numbers

        .global Gen_fibo

//      x0 = fibo,       x1 = n
//      x9 = i,          x10 = temporary,   x11 = fibo[i-2]
//      x12 = fibo[i-1]  x13 = fibo[i],     x14 = &fibo[i]
Gen_fibo:
        // fibo[0] and fibo[1] are done by hands
        stur    xzr, [x0,0]       // fibo[0] = 0;
        mov     x10, 1            // Can't stur immed
        stur    x10, [x0,8]       // fibo[1] = 1;

        // Initialization
        mov     x11, 0          // x11 = fibo[i-2]
        mov     x12, 1          // x12 = fibo[i-1]
        mov     x9, 2           // i = 2

  Test: subs    xzr, x9, x1     // Set flags for comparison of i and n
        b.ge    Done            // i >= n quit

        add     x13, x11, x12   // fibo[i] = fibo[i-1] + fibo[i-2]
        lsl     x10, x9, 3      // x10 = i*8
        add     x14, x0, x10    // x14 = &fibo[i]
        stur    x13, [x14, 0]   // fibo[i] = x13
        mov     x11, x12        // fibo[i-2] = fibo[i-1]
        mov     x12, x13        // fibo[i-1] = fibo[i]

        add     x9, x9, 1       // i++
        b       Test

  Done: br      lr
