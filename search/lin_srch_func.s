//      File:      lin_srch_func.s

//      Function:  Lin_srch
//      Purpose:   Implement recursive linear search of an array
//      In args:   list = x0
//                 n = x1
//                 val = value we're searching for
//                 curr = subscript we're currently checking
//      Ret val:   The subscript of val, if it's in the list,
//                 -1 otherwise
        .global Lin_srch

//      x0 = x19 = list,   x1 = n,  x2 = val, x3 = curr.
Lin_srch:
        sub     sp, sp, 16      // Add storage for 2 long words
        stur    lr, [sp, 8]     // Push return address
        stur    x19, [sp, 0]    // Push x19 = list

        sub     x9, x1, x3      // x9 = n - curr
        cbnz    x9, Chk_list    // n > curr, continue search

        mov     x0, -1          // val isn't in list
                                // Set ret val to -1
        b       Done

Chk_list:
        mov     x19, x0         // x19 = list
        lsl     x10, x3, 3      // x10 = 8*curr, Offset in bytes
        add     x10, x19, x10   // x10 = &list[curr]
        ldur    x10, [x10, 0]   // x10 = list[curr]

        sub     x9, x2, x10     // x9 = val - list[curr]
        cbnz    x9, Cont_srch   // if val != list[curr], cont search

        mov     x0, x3          // We found val
        b       Done

Cont_srch:
        add     x3, x3, 1       // curr++
        bl      Lin_srch        // Recursive call
                                // Result is in x0

  Done: ldur    lr, [sp, 8]     // Restore lr from stack
        ldur    x19, [sp, 0]    // Restore x19 from stack
        add     sp, sp, 16      // Reset stack pointer
        br      lr
