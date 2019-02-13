        .global Lock

//      x0 stores the address of the lock
//      x1 should store the value 1
//      Note that w9 (the first operand in stxr) must be 32-bit

Lock:  

        ldxr x10, [x0, 0]   // lock address in x0
                            //    load its contents, start monitoring x0
        cbnz x10, Lock      // if x10 != 0, another thread owns the lock
                            //    start over
        stxr w9, x1, [x0]   // lock may be available. 
                            //    Try to acquire it by storing 1
                            //    success (0) or failure (1) in w9
        cbnz w9, Lock       // if lock acquisition failed start over
                            //    else, we acquired the lock
        br  lr


        .global Unlock

//      x0 stores the address of the lock
//      Assumes stur is atomic

Unlock:  
        stur xzr, [x0, #0]    // Relinquish the lock
        ret
