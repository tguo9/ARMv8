        .global Lock
        // UNLOCKED = 0
        // LOCKED = 1
        // x0 = &spinlock
Lock:

While:  ldur  x9, [x0,0]    // x9 = value of spinlock
        cbz   x9, Got_lock  // x9 = 0 => unlocked
        b     While         // Try again

Got_lock:
        mov   x9, 1         // x9 = locked
        stur  x9, [x0, 0]   // spinlock is locked
        br    lr


       .global Unlock
       // x0 = &spinlock
Unlock:
       stur xzr, [x0, 0]    // spinlock is unlocked
       br   lr 
