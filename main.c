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
#include <shapes.h>

int8* heap_ptr;
extern boolean videoinit;

void main(){
    heap_ptr = &heap;
    videoinit = false;
    videomode(TEXT40x25);
    point* pt1 = mkpoint(1, 10, 0);
    point* pt2 = mkpoint(20, 10, 0);
    line* line = mkline(pt1, pt2, 0, 2);
    drawline(line);
    freeall();
}


void putchar(int8 c){
    bputchar(c);
}

int8 getchar(void){
    int8 al, ah;
    int16 ax;
    ax = bgetchar();
    al = ax & 0xff;
    ah = (ax & 0xff00) >> 0x8;
    return al ? al : ah;
}

void print(int8* str){
    int8* p;
    for(p=str; *p; p++){
        putchar(*p);
    }
}

void* alloc(int16 size){
    void* p;
    if(size <= 0)return $v 0;
    p = $v heap_ptr;
    heap_ptr = heap_ptr + size;
    return p;
}

void freeall(void){
    heap_ptr = &heap;
    return;
}




