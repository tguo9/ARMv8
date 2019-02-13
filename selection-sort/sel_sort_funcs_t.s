//      File:             sel_sort_funcs_t.s

//      Function:         Sel_sort      
//      Purpose:          Implement selection sort for a list of long ints
//      Input arg:        x1:  n:  the number of elements in the list
//      Input/Output arg: x0:  the address of the list
//      Note:             This version uses *caller-save* registers

  	.global	Sel_sort

//      x0 = list, x1 = n  
//      x11 = i,   x12 = n-1
Sel_sort:
        // Set up stack
        sub     sp, sp, 48    // Make room on the stack for 
                              //    lr, x9, x10, x11, x12
                              // ARMv8 doesn't like multiples of 1
                              //    word:  it wants multiples of 2
                              //    words
                              // So subtract 6*8 = 48, instead of
                              //    5*8 = 40
        stur    lr,  [sp, 32] // Push lr
    //  stur    x12, [sp, 24] // Push n-1
    //  stur    x11, [sp, 16] // Push i
    //  stur    x1, [sp,  8]  // Push n
    //  stur    x0, [sp,  0]  // Push list

        // Initialization
        mov     x11, 0        // x11 = 0 = i
        sub     x12, x1, 1    // x12 = n - 1

        // list, n-1, n won't change:  only need to be pushed once
        stur    x12, [sp, 24] // Push n-1, won't change
        stur    x1, [sp,  8]  // Push n, won't change
        stur    x0, [sp,  0]  // Push list, won't change


Lp_tst: subs    xzr, x11, x12 // Compare i and (n-1)
        b.ge    Done_ss       // if i >= n-1 done

        stur    x11, [sp, 16] // Push i, changes every iteration
        // i < n-1, list, n, i, n-1 are all in 
        //    caller-saved registers
        ldur    x0, [sp, 0]   // Load list
        mov     x1, x11       // x11 = i
        ldur    x2, [sp, 8]   // Load n
        bl      Find_min      // Call Find_min    

        mov     x2, x0        // x0 = j = minloc
        ldur    x0, [sp, 0]   // x0 = list
        ldur    x1, [sp, 16]  // x1 = i
        bl      Swap          // Call Swap

        ldur    x11, [sp, 16] // x11 = i
        ldur    x12, [sp, 24] // x12 = n-1
        add     x11, x11, 1   // i++
        b       Lp_tst

Done_ss:  
        ldur    lr,  [sp, 32] // Pop lr
        add     sp, sp, 48    // Move sp to position when 
                              //    Sub_add was called.
 
        // Return to the caller, return values in addresses x3 and x4
	// ret
        br      lr

//---------------------------------------------------------------------
//      Function:   Swap
//      Purpose:    Swap the elements in list[i] and list[j]
//      Input args: x1 = i
//                  x2 = j 
//      In/out arg: x0 = list

  	.global	Swap

//      x0 = list, x1 = i, x2 = j
//      x9 = &list[i], x10 = &list[j]
//      x11 = list[i], x12 = list[j]
Swap:
        lsl     x9, x1, 3     // x9 = 8*i
        add     x9, x9, x0    // x9 = &list[i]
	ldur    x11, [x9, 0]  // x11 = list[i]

        lsl     x10, x2, 3    // x10 = 8*j
        add     x10, x10, x0  // x10 = &list[i]
        ldur    x12, [x10, 0] // x12 = list[j]

        stur    x12, [x9, 0]  // Store list[j] into &list[i]
        stur    x11, [x10, 0] // Store list[i] into &list[j]

        // Return to the caller, return value in x0
	// ret
        br      lr


//---------------------------------------------------------------------
//      Function:   Find_min
//      Purpose:    Find the subscript of the smallest element arr[i],
//                  where min <= i < max and arr is an array of long ints
//      Input args: x0 = arr
//                  x1 = min
//                  x2 = max
//      Ret val:    x0 = i
//  
//      Note:       0 <= min < max <= number of elements in arr.

  	.global	Find_min

//      In args:     x0 = arr, x1 = min, x2 = max 
//      Temporaries: x10 = minloc, x11 = minval
//                   x12 = i 
//                   x13 = arr + 8*i (8*i = i converted to bytes)
//                   x14 = arr[i]
Find_min:
        // Initialization
        mov     x10, x1       // x10 = minloc = min
        mov     x12, x1       // i = min
        lsl     x13, x12, 3   // Convert to bytes
        add     x13, x0, x13  // Convert to absolute address
        ldur    x11, [x13,0]  // x11 = arr[min] = minval 

        add     x12, x12, 1   // i = min + 1

        // Loop
  Test: subs    xzr, x12, x2  // Subtract i - max to set flags
        b.ge    Done_fm
        
        add     x13, x13, 8   // Get address of arr[i] 
        ldur    x14, [x13,0]  // x14 = arr[i]

        subs    xzr, x14, x11 // Subtract arr[i] - minval to set flags
        b.ge    Cont          // Don't update minloc, minval if
                              //    arr[i] >= minval

        // arr[i] < minval
        mov     x10, x12      // minloc = i
        mov     x11, x14      // minval = arr[i]

  Cont: add     x12, x12, 1   // i++
        b       Test          // Go back to beginning of loop

Done_fm: 
        mov     x0, x10       // Return value = sum = x11

        // Return to the caller, return value in x0
	// ret
        br      lr
