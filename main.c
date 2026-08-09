/* main.c */

/* CPU starts in 16-bit real mode after reset. We need to tell the assembler to interpret the following code in 16-bit
** mode
*/

 asm(
    ".code16gcc\n" 
    "call main\n"
    "call exit\n"
);

#include <gui.h>
#include <assembly.h>

int8* heap_ptr;

void main(){
    int8* p;
    heap_ptr = &heap;
    p = $1 alloc(9);
    p[0] = 'B';
    p[1] = 'E';
    p[2] = 'N';
    p[3] = 'E';
    p[4] = 'D';
    p[5] = 'I';
    p[6] = 'C';
    p[7] = 'T';
    p[8] = '\0';

    print($1 p);
    freeall();
    print($1 "Hello world!\r\n");
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

void* alloc(int16 size){
    int8* p;
    if(size <= 0)return $v 0;
    p = heap_ptr;
    heap_ptr = $1 heap_ptr + size;
    return p;
}

void freeall(void){
    heap_ptr = &heap;
    return;
}
