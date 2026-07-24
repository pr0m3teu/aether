%macro ISR_NOERRCODE 1
    global isr%1
    isr%1:
        cli
        push byte 0  ; trapframe->err
        push byte %1 ; trapframe->trapno
        jmp alltraps
%endmacro


%macro ISR_ERRCODE 1
    global isr%1
    isr%1:
        cli
        push byte %1 ; trapfram->trapno
        jmp alltraps

%endmacro

extern exception_handler

ISR_NOERRCODE  0
ISR_NOERRCODE  1
ISR_NOERRCODE  2
ISR_NOERRCODE  3
ISR_NOERRCODE  4
ISR_NOERRCODE  5
ISR_NOERRCODE  6
ISR_NOERRCODE  7
ISR_ERRCODE    8
ISR_NOERRCODE  9
ISR_ERRCODE   10 
ISR_ERRCODE   11 
ISR_ERRCODE   12 
ISR_ERRCODE   13 
ISR_ERRCODE   14 
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE   17 
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20 
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31 


alltraps:
    call exception_handler
    add esp, 0x8
    iret

