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

int8 *heap_ptr;
extern boolean videoinit;

void main()
{
    heap_ptr = &heap;
    videoinit = false;
    videomode(BGFX640x480);

    // int8 color = 2;
    // point *pt1 = mkpoint(100, 100, color);
    // point *pt2 = mkpoint(400, 400, color);

    // rectangle *rect = mkrectangle(pt1, pt2, color, color, 4, 1);

    // drawrectangle(rect);
    bitmap *bmp;
    boolean ret;

    bmp = parsebmp($1 "penguin");
    if (!bmp)
    {
        print($1 "Error\n");
        freeall();
        return;
    }

    ret = drawbmp(bmp, 10, 10);
    if (ret)
        print($1 "true");
    else
        print($1 "false");

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

void copy(int8 *dst, int8 *src, int16 size)
{
    int16 n;
    int8 *dst_ptr;
    int8 *src_ptr;

    for (n = 0, dst_ptr = dst, src_ptr = src; n < size; n++, dst_ptr++, src_ptr++)
    {
        *dst_ptr = *src_ptr;
    }
    return;
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

void set(int8 *dst, int8 c, int16 size)
{
    int16 n;
    int8 *ptr;

    for (n = 0, ptr = dst; n < size; n++, ptr++)
        *ptr = c;
}

int16 stringlen(int8 *str)
{
    if (!str)
        return 0;
    int16 len;
    int8 *ptr;

    len = 0;
    ptr = str;
    while (*ptr)
    {
        len++;
        ptr++;
    }
    return len;
}
