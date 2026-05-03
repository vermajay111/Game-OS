[org 0x7c00]

mov [BOOT_DRIVE], dl

mov bp, 0x9000       
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string_16
call load_kernel

mov ah, 0x00
mov al, 0x13
int 0x10

cli
lgdt [gdt_descriptor]

mov eax, cr0
or eax, 0x1
mov cr0, eax

jmp 0x08:init_pm 

[bits 16]
print_string_16:
    mov ah, 0x0e
    .loop:
        mov al, [bx]
        cmp al, 0
        je .done
        int 0x10
        add bx, 1
        jmp .loop
    .done:
        ret

load_kernel:
    mov ax, 0x1000
    mov es, ax
    xor bx, bx
    mov dh, 20
    mov dl, [BOOT_DRIVE]
    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    int 0x13
    ret

BOOT_DRIVE db 0

[bits 32]
init_pm:
    mov ax, 0x10       
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000    
    mov esp, ebp

    call BEGIN_PM

BEGIN_PM:
    jmp 0x10000

MSG_REAL_MODE db "Started in 16-bit real mode", 0

%include "src/boot/gdt.asm"

times 510-($-$$) db 0
dw 0xaa55