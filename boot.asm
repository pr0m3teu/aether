org 0x7C00

bits 16

jmp _start

msg db "Hello, World!", 10, 13, 0

hello_world:
    lodsb
    or al, al
    jz done 
    mov ah, 0x0E
    int 0x10
    jmp hello_world

done:
    ret

_start:
    cld
    xor bx, bx
    xor ax, ax
    mov ds, ax
    mov es, ax

    mov si, msg
    call hello_world

    cli
    hlt


times 510 - ($-$$) db 0
dw 0xAA55



