; bgfx.asm
bits 16
%include "bgfx.h"

global exit
global bputchar

	; AH = 0E
	; AL = ASCII character to write
	; BH = page number (text modes)
	; BL = foreground pixel color (graphics modes)
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
