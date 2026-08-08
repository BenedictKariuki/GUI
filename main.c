/* main.c */

/* CPU starts in 16-bit real mode after reset. We need to tell the assembler to interpret the following code in 16-bit
** mode
*/

 asm(
    ".code16gcc\n" 
    "call main\n"
    "call exit\n"
);

#include <gui.h> // types
#include <assembly.h>


void main(){
    print($1 "Hello world!\n");
}

void putchar(int8 c){
    bputchar(c);
}

void print(int8* str){
    int8* p;
    for(p=str; *p; p++){
        putchar(*p);
    }
}

