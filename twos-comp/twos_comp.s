        // File:      twos_comp.s
        // Purpose:   Find the absolute value of the input arg
        //            using two's complement

        // Function:  Twos_comp
        // Purpose:   Take the two's complement of the arg
        // In arg:    x0 signed long int
        // Ret val:   x0, two's complement of input arg
        // Algorithm: Store 0xffff ffff ffff ffff in x9
        //            Get one's complement of x0 by
        //               taking exclusive or of x0 with
        //               x9 and storing this in x10
        //            Get two's complement of x0 by 
        //               adding 1 to x10
        // Note:      eor doesn't seem to work.  So
        //               we used bic.
        .global Twos_comp

Twos_comp:
        // Store 0xffff ffff ffff ffff in x9
        movz    x9, 65535, lsl 48
        movk    x9, 65535, lsl 32
        movk    x9, 65535, lsl 16
        movk    x9, 65535, lsl  0

        bic     x10, x9, x0     // x10 = ~x0, eor crashes
        add     x0, x10, 1      // x0 = two's comp of x0
        br      lr


        // Function:  Abs_val
        // Purpose:   Find the absolute value of the input arg
        // In arg:    x0 (signed long int)
        // Ret val:   x0 (unsigned long int)
        // Algorithm: if x0 < 0 take its twos complement
        // Note:      if x0 = 0x8000 0000 0000 0000, the two's
        //               complement is also 0x8000 0000 0000 0000 =
        //               -2^63 as a signed int, but 2^63 as an
        //               unsigned int. 
        .global Abs_val
Abs_val: 
        sub     sp, sp, 16      // Increase stack size (corrected)
        stur    lr, [sp, 0]     // Push return address

        cmp     x0, xzr         // Compare x0, 0
        b.ge    Done            // If x0 >= 0 do nothing
        bl      Twos_comp       // Take two's complement of x0

Done:   ldur    lr, [sp, 0]     // Pop return address
        add     sp, sp, 16      // Restore stack pointer (corrected)
        br      lr              
