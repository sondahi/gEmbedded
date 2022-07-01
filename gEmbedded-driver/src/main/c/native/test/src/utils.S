.global delay
delay:
    subs r2, r2, #1
    bne delay
    bx lr

.global add
add:
    add r0, r0, r1
    bx lr