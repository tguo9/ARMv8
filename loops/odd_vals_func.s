//     File:  odd_vals_func.s

//     Function:  Assign_odds
//     Purpose:   Store the first n positive odd integers in an
//                array
//     In arg:    x1 = n = number of odd integers
//     Out arg:   x0 = odd_vals = the odd integers

       .global Assign_odds

//     x0 = odd_vals array,  x1 = n
//     x9 = i,   x10 = 2*i+1,  x11 = &odd_vals[i]
Assign_odds:
       mov     x9, 0          // x9 = i = 0

 Test: subs    xzr, x9, x1    // Test i >= n
       b.ge    Done           // i >= n, return

       // i < n
       lsl     x10, x9, 1     // x10 = 2*x9 = 2i
       add     x10, x10, 1    // x10 = 2i + 1

       lsl     x11, x9, 3     // x11 = 8*i
       add     x11, x11, x0   // x11 = x0 + 8*i = &odd_vals[i]
       stur    x10, [x11, 0]  // arr[i] = x10 = 2*i+1

       add     x9, x9, 1      // i++
       b       Test           // Go to start of loop

 Done: br      lr             // return
