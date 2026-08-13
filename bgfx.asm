; bgfx.asm

bits 16
%include "bgfx.h"

global exit
global bputchar
global bvideomode
global bgetchar
global bdrawpointT


exit:
    mov ax, 0x4c00
    int 0x21
    ;push bp
    ;mov bp, sp

    ;xor ax, ax      ; we want ax to be zero. DOS function calls preserve the contents of all the registers except the AX register.
    ;int 0x21        ; 

    ;.halt:
     ;   cli         ; clear interrupt flag
      ;  hlt         ; stop the CPU until a hardware interrupt occurs
        ;jmp .halt   ; loop back to the halt location   

        ;mov sp, bp
        ;pop bp
        ;ret

bputchar:
        push bp
        mov bp, sp

        arg ax, 0
        mov ah, 0x0e
        xor bx, bx
        int 0x10

        mov sp, bp
        pop bp
        ret

bvideomode:
        push bp
        mov bp, sp

        arg ax, 0
        xor ah, ah
        int 0x10

        mov sp, bp
        pop bp
        ret

bgetchar:
        push bp
        mov bp, sp
        
        xor ax, ax
        int 0x16
        
        mov sp, bp
        pop bp
        ret

bdrawpointT:
        push bp
        mov bp, sp
        
        ; set the cursor position
        arg ax, 0
        arg dx, 1

        and dx, 0xff
        mov dh, al
        xor ax, ax
        mov ah, 0x2
        xor bx, bx
        int 0x10
        
        ; draw character at cursor
        mov al, '+'
        mov ah, 0x0a
        xor bx, bx
        mov cx, 0x01
        int 0x10

        ;mov ax, 0x01
        mov sp, bp
        pop bp
        ret
        
