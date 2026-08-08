; bgfx.h
bits 16

; This macro takes a two arguments. The first argument is treated as a register and
; the second argument is treated as the position of the argument that you want to 
; read from the stack, e.g., 1st, 2nd. It calculates the offset of that argument, 
; reads the stack from that offset and stores that into the register you provided 
; as the first argument to the macro.

%macro arg 2
    %%of equ ((4*%2)+6)
    mov %1, [bp+%%of]
%endmacro
