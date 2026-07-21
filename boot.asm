org 0x7c00

bits 16

KERNEL_ENTRY equ 0x10000

section .text
jmp _start

print_string:
    lodsb
    or al, al
    jz done 
    mov ah, 0x0E
    int 0x10
    jmp print_string 
done:
    ret


; load dh sectors to es:bx from drive dl
disk_load:
    pushf
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
    popf
    ret
disk_error:
    mov si, DISK_ERROR_MSG
    call print_string 
    jmp $
        

_start:
    cld
    ; Initializing segments
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    mov si, msg 
    call print_string 

    ; Load Kernel
    mov si, LOADING_KERNEL
    call print_string

    mov ax, 0x1000
    mov es, ax 
    mov bx, 0x0000
    mov dh, 0x1

    call disk_load

    mov si, LOADED_KERNEL
    call print_string

    ; Prepare for Protected Mode
    cli ; TODO: also dissable NMI (Non-Maskable Interrupt)

    ; Enable A20Line (see: https://wiki.osdev.org/A20_Line)
    ; TODO: Check if it isn't already enabled
a20.1:
    in al, 0x64
    test al, 0x2
    jnz a20.1

    mov al, 0xd1
    out 0x64, al

a20.2:
    in al, 0x64
    test al, 0x2
    jnz a20.2

    mov al, 0xdf
    out 0x64, al

GDT:
    ; Loading GDT
    lgdt [gdt_descriptor]

    ; Entering protected mode
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

reload_cs:
    jmp 0x08:reload_segments

; Protected Mode
bits 32
reload_segments: ; Protected Mode Flat Model
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000
    
    jmp KERNEL_ENTRY
    

; Setting up GDT
gdt_start:
gdt_null: ; Null Descriptor
    dq 0x0 

gdt_code: ; Kernel Mode Code Segment
    dw 0xffff ; Limit [15:0]
    dw 0x0000 ; Base  [15:0]
    db 0x00   ; Base  [23:16]
    db 0x9a   ; Access Byte
    db 0xcf   ; Flags + Limit [19: 16] 
    db 0x00   ; Base [31:24]

gdt_data: ; Kernel Mode Data Segment
    dw 0xffff ; Limit [15:0]
    dw 0x0000 ; Base  [15:0]
    db 0x00   ; Base  [23:16]
    db 0x92   ; Access Byte
    db 0xcf   ; Flags + Limit [19: 16] 
    db 0x00   ; Base [31:24]
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; GDTR(Limit)
    dd gdt_start                ; GDTR(Base)
                                ; See https://www.felixcloutier.com/x86/lgdt:lidt

msg db "Welcome to project Aether!", 10, 13, 0
LOADING_KERNEL db "[INFO] Loading Kernel...", 10, 13, 0
LOADED_KERNEL  db "[INFO] Successfully loaded Kernel", 10, 13, 0
DISK_ERROR_MSG db "[ERROR] Could not read from disk!", 10, 13, 0


times 510 - ($-$$) db 0
dw 0xAA55



