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
    videomode(BGFX640x480);

    int8 color = 2;
    point* pt1 = mkpoint(100, 100, color);
    point* pt2 = mkpoint(400, 400, color);

    rectangle* rect = mkrectangle(pt1, pt2, color, color, 4, 1);

    drawrectangle(rect);
    
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
}

void copy(int8* dst, int8* src, int16 size){
    int16 n;
    int8* dst_ptr;
    int8* src_ptr;

    for(n=0, dst_ptr=dst, src_ptr=src; n < size; n++, dst_ptr++, src_ptr++){
        *dst_ptr = *src_ptr;
    }
    return;
}





