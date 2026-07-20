org 0x7C00

bits 16

jmp _start

msg db "Hello, World!", 10, 13, 0

print_string:
    lodsb
    or al, al
    jz done 
    mov ah, 0x0E
    int 0x10
    jmp print_string 

done:
    ret


_start:
    cld
    xor bx, bx
    xor ax, ax
    mov ds, ax
    mov es, ax

    mov si, msg
    call print_string 

    cli
    hlt

; load dh sectors to es:bx from drive dl
disk_load:
   push dx

   mov ah, 0x2
   mov al, dh ; read dh sectors
   mov ch, 0x0 ; select cylinder 0
   mov dh, 0x0 ; select track 0
   mov cl, 0x2 ; read starting from 2nd sector (1st sector is the boot sector)
   
   int 0x13

    jc disk_error
    pop dx
    cmp dh, al
    jne disk_error
    ret

disk_error:
    mov si, DISK_ERROR_MSG
    call print_string 
    jmp $
        

DISK_ERROR_MSG db "[ERROR] Could not read from disk!", 10, 13, 0

times 510 - ($-$$) db 0
dw 0xAA55



