; bgfx.asm
bits 16
%include "bgfx.h"
global exit

exit:
    push bp
    mov bp, sp

    xor ax, ax      ; we want ax to be zero. DOS function calls preserve the contents of all the registers except the AX register.
    int 0x21        ; 

    .halt:
        cli         ; clear interrupt flag
        hlt         ; stop the CPU until a hardware interrupt occurs
        jmp .halt   ; loop back to the halt location   

        mov sp, bp
        pop bp
        ret
