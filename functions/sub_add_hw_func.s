//      File:        sub_add_hw_func.s

//      Function:    Sub_add      
//      Purpose:     Compute a - b + c for long ints a, b, and c.
//                   Return a-b+c
//      Input args:  x0, x1, x2, pointers to the three numbers a, b, c
//      Ret value:   x0 = a - b + c

//	The ``.global'' informs the linker that this code can
//         be called by code in other files
  	.global	Sub_add

Sub_add:
        ldur    x9,  [x0, 0]  // Load a into x9
        ldur    x10, [x1, 0]  // Load b into x10
        ldur    x11, [x2, 0]  // Load c into x11

        sub     x12, x9, x10  // x12 = x0 - x1 = a - b
        add     x0,  x12, x11 // x0 = x12 + x11 = a - b + c


        // Return to the caller, return values in addresses x3 and x4
        br      lr

