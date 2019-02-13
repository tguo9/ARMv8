//      File:       find_min_func.s

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
        mov     x10, x1       // x10 = minloc
        mov     x12, x1       // i = min
        lsl     x13, x12, 3   // Convert to bytes
        add     x13, x0, x13  // Convert to absolute address
        ldur    x11, [x13,0]  // x11 = arr[min] = minval 

        add     x12, x12, 1   // i = min + 1

        // Loop
  Test: subs    xzr, x12, x2  // Set flags for i >= max
        b.ge    Done
        
        add     x13, x13, 8   // Get address of arr[i] 
        ldur    x14, [x13,0]  // x14 = arr[i]

        subs    xzr, x14, x11 // Set flags for arr[i] >= minval
        b.ge    Cont          // Don't update minloc, minval if
                              //    arr[i] >= minval

        // arr[i] < minval
        mov     x10, x12      // minloc = i
        mov     x11, x14      // minval = arr[i]

  Cont: add     x12, x12, 1   // i++
        b       Test          // Go back to beginning of loop

Done:   mov     x0, x10       // Return value = minloc = x10

        // Return to the caller, return value in x0
	// ret
        br      lr
