//      File:        sub_add_func.s

//      Function:    Sub_add      
//      Purpose:     Implement a - b + c for long ints a, b, and c.
//                   Return a-b and a-b+c
//      Input args:  x0, x1, x2, the three numbers a, b, c
//      Output args: x3 = address of a - b
//                   x4 = address of a - b + c

//	The ``.global'' informs the linker that this code can
//         be called by code in other files
  	.global	Sub_add

Sub_add:
        // Add the contents of registers x0 and x1, storing the
        // result in x0
        sub     sp, sp, 16  // Make room on the stack for lr
                            // ARMv8 doesn't like multiples of 1
                            //    word:  it wants multiples of 2
                            //    words
        stur    lr, [sp, 8] // Store lr on stack
        stur    x4, [sp, 0] // Store x4 on top of stack

        sub     x9, x0, x1  // x9 = x0 - x1 = a - b

        stur    x9, [x3, 0] // Save x9 = a - b in the address in x3
        mov     x0, x9      // x0 = a - b
        mov     x1, x2      // x1 = c
        bl      Add         // Add(a-b, c)

        ldur    x4, [sp, 0] // Get x4 = address of a-b+c
        stur    x0, [x4, 0] // x0 = a - b + c, save in address in x4

        ldur    lr, [sp, 8] // Get lr = return address off stack
        add     sp, sp, 16  // Return sp to position when Sub_add was 
                            //    called.

        // Return to the caller, return values in addresses x3 and x4
	// ret
        br      lr

//---------------------------------------------------------------------
//      Function:   Add
//      Purpose:    Implement addition of two long ints in ARMv8
//      Input args: x0, x1, the two numbers being added
//      Ret val:    x0, the sum of the two input values

//	The ``.global'' informs the linker that this code can
//         be called by code in other files
  	.global	Add

Add:
        // Add the contents of registers x0 and x1, storing the
        // result in x0
	add	x0, x1, x0

        // Return to the caller, return value in x0
	// ret
        br      lr
