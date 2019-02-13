//      File:             count_sort_funcs.s
//      Purpose:          Implement the functions Count_sort, Count_lt,
//                        and Copy_list in ARMv8

//      Function:         Count_sort      
//      Purpose:          Implement count sort for a list of long ints
//      Input arg:        x1:  n:  the number of elements in the list
//      Input/Output arg: x0:  the address of the list

  	.global	Count_sort

//      x19 = list, x20 = n
//      x21 = i, x22 = temp  
Count_sort:
        // Set up stack
        sub     sp, sp, 848    // Make room on the stack for 
                               //    lr, x19, x20, x21, x22, and temp
                               //    = 105*8 = 840 words
                               // ARMv8 doesn't like multiples of 1
                               //    word:  it wants multiples of 2
                               //    words
                               // So subtract 106*8 = 848, instead of
                               //    105*8 = 840
        stur    lr,  [sp, 32]  // Push lr
        stur    x22, [sp, 24]  // Push x22
        stur    x21, [sp, 16]  // Push x21
        stur    x20, [sp, 8]   // Push x20
        stur    x19, [sp, 0]   // Push x19

        // Initialization
        mov     x19, x0       // x19 = list
        mov     x20, x1       // x20 = n
        mov     x21, 0        // i = x21 = 0
        add     x22, sp, 40   // x22 = temp

Lp_tst: subs    xzr, x21, x20 // Compare i and n
        b.ge    Done_cs       // if i >= n done

        // i < n, list, n, i, temp are all in 
        //    callee-saved registers
        mov     x0, x19       // x19 = list
        mov     x1, x20       // x20 = n
        mov     x2, x21       // x21 = i
        bl      Count_lt      // Call Count_lt    

        lsl     x9, x21, 3    // x9 = 8*i
        add     x10, x19, x9  // x10 = &list[i]
        ldur    x11, [x10, 0] // x11 = list[i]

        lsl     x9, x0, 3     // x9 = 8*j
        add     x10, x22, x9  // x10 = &temp[j]
        stur    x11, [x10, 0] // temp[j] = list[i]

        add     x21, x21, 1   // i++
        b       Lp_tst

Done_cs:  
        mov      x0, x19       // x0 = list
        mov      x1, x22       // x1 = temp
        mov      x2, x20       // x2 = n
        bl       Copy_list

        ldur    lr,  [sp, 32] // Pop lr
        ldur    x22, [sp, 24] // Pop x22
        ldur    x21, [sp, 16] // Pop x21
        ldur    x20, [sp, 8] // Pop x20
        ldur    x19, [sp, 0] // Pop x19

        add     sp, sp, 848    // Move sp to position when 
                               //    Count_sort was called.
 
        // Return to the caller
        br      lr

//---------------------------------------------------------------------
//      Function:   Count_lt
//      Purpose:    Count the number of elements in list that are
//                  "<" list[i]
//      Input args: x0 = list
//                  x1 = n
//                  x2 = i
//      Ret val:    x0 = j = number of elements < list[i]
//  
//      Note:       list[j] "<" list[i] if
//                  - list[j] < list[i] or
//                  - list[j] = list[i] and j < i 

  	.global	Count_lt

//      In args:     x0 = list, x1 = n, x2 = i 
//      Temporaries: x9 = less_than
//                   x10 = list[i] 
//                   x11 = j
//                   x12 = &list[j]
//                   x13 = list[j]
Count_lt:
        // Initialization
        lsl     x9, x2, 3     // x9 = 8*i
        add     x9, x0, x9    // x9 = &list[i]
        ldur    x10, [x9, 0]  // x10 = list[i]

        mov     x9, 0         // x9 = less_than = 0
        mov     x11, 0        // x11 = j = 0

        // Loop
  Test: subs    xzr, x11, x1  // Compare i, n
        b.ge    Done_clt      // If i >= n done
        
        lsl     x12, x11, 3   // x12 = 8*j
        add     x12, x0, x12  // x12 = &list[j]
        ldur    x13, [x12,0]  // x13 = list[j]

        subs    xzr, x13, x10 // Compare list[j], list[i]
        b.gt    Cont          // If list[j] > list[i]
                              //    Don't update less_than
        b.eq    Equal

        // list[j] < list[i]
        add     x9, x9, 1     // less_than++
        b       Cont

 Equal: // list[j] = list[i]
        subs   xzr, x11, x2   // Compare j, i
        b.ge   Cont           // If j >= i don't update
        add    x9, x9, 1      // less_than++

  Cont: add     x11, x11, 1   // j++
        b       Test          // Go back to beginning of loop

Done_clt: 
        mov     x0, x9        // Return value = x9 = less_than

        // Return to the caller, return value in x0
        br      lr


//---------------------------------------------------------------------
//      Function:   Copy_list
//      Purpose:    Copy the first n elements of inlist into 
//                  the first n slots in outlist
//      Input args: x1 = inlist
//                  x2 = n 
//      In/out arg: x0 = outlist

  	.global	Copy_list

//      x0 = outlist, x1 = inlist, x2 = n
//      x9 = i
//      x10 = &inlist[i], x11 = inlist[i]
//      x12 = &outlist[i]
Copy_list:
        // Initialization
        mov     x9, 0          // x9 = i = 0

Cl_loop:
        subs    xzr, x9, x2   // Compare i, n
        b.ge    Done_cl       // If i >= n done

        lsl     x10, x9, 3    // x10 = 8*i
        add     x12, x0, x10  // x12 = &outlist[i]
        add     x10, x1, x10  // x10 = &inlist[i]
        ldur    x11, [x10, 0] // x11 = inlist[i]
        stur    x11, [x12, 0] // outlist[i] = inlist[i]

        add     x9, x9, 1     // i++
        b       Cl_loop 

Done_cl:// Return to the caller, return value in x0
	// ret
        br      lr


