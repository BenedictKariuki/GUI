/* bmp.h */

#pragma once
#include <gui.h>
#include <shapes.h>

#define GETCOLOR(x, y) (y)

/* bitmap header - 14 bytes */
struct s_bmp_header
{
    int16 signature;
    int fSize;
    int _;
    int offset;
} packed;
typedef struct s_bmp_header bmp_header;

/* bitmap info header - 40 bytes */
struct s_info_header
{
    int size;
    int width;
    int height;
    int16 _;
    int16 __;
    int ___;
    int ____;
    int _____;
    int ______;
    int _______;
    int ________;
} packed;
typedef struct s_info_header info_header;

/* bitmap color table - 4 * NumColors bytes */

typedef rgb color_table[16];

struct s_bitmap
{
    int8 *filename;
    int16 x, y;
    bmp_header *hdr;
    info_header *info_hdr;
    color_table *colors;
} packed;

typedef struct s_bitmap bitmap;

bitmap *parsebmp(int8 *);
boolean drawbmp(bitmap *, int16, int16);
int8 *addbmp(int8 *);
int8 getcolor(color_table *, int8);
