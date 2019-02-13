//      File:     add2_func.s
//      Purpose:  Implement addition of two long ints in ARMv8.  This
//                version is passed pointers to the input values and
//                the result
//      Input args: x0, x1 addresses of the two numbers being added
//      Output arg: x2 address of the sum

//	Needed to inform compiler that this can be called by code
//         in other files
  	.global	Add

Add:
        ldur    x9, [x0, 0]
        ldur    x10, [x1, 0]
	add	x11, x9, x10
        stur    x11, [x2, 0]
	br      lr
