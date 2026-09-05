/* main.c */

/* CPU starts in 16-bit real mode after reset. We need to tell the assembler to interpret the following code in 16-bit
** mode
*/

asm(
    ".code16gcc\n"
    "call main\n"
    "call exit\n");

#include <gui.h>
#include <assembly.h>
#include <shapes.h>
#include <bmp.h>
#include <omnistd.h>

int8 *heap_ptr;
extern boolean videoinit;
rgb **globalcolors;

void main()
{
    heap_ptr = &heap;
    videoinit = false;
    videomode(BGFX640x480);
    globalcolors = (rgb **)0;
    globalcolors = setpalettes();

    bitmap *bmp;
    boolean ret;

    bmp = parsebmp($1 "penguin");
    if (!bmp)
    {
        print($1 "Error\r\n");
        freeall();
        return;
    }

    ret = drawbmp(bmp, 50, 50);

    freeall();
}

void putchar(int8 c)
{
    bputchar(c);
}

int8 getchar(void)
{
    int8 al, ah;
    int16 ax;
    ax = bgetchar();
    al = ax & 0xff;
    ah = (ax & 0xff00) >> 0x8;
    return al ? al : ah;
}

void print(int8 *str)
{
    int8 *p;
    for (p = str; *p; p++)
    {
        putchar(*p);
    }
}

void *alloc(int16 size)
{
    void *p;
    if (size <= 0)
        return $v 0;
    p = $v heap_ptr;
    heap_ptr = heap_ptr + size;
    return p;
}

void freeall(void)
{
    heap_ptr = &heap;
}

int16 open(int8 *filename, int16 offset)
{
    int16 fd, mv;
    fd = bopen(filename);
    if (!fd)
        return 0;
    mv = bmove(fd, offset);
    if (!mv)
    {
        close(fd);
        return 0;
    }
    return fd;
}

int8 read(int16 fd)
{
    return bread(fd);
}

void close(int16 fd)
{
    bclose(fd);
}

/*void main()
{
    freeall();

    PRINTF($1 "Hello %s from %s %X\n", $1 "world", $1 "the land of C.", 125);

    // int8 *p;
    // p = int2hex(125);
    // print(p);

    return;
}*/