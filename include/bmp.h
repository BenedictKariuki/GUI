/* bmp.h */

#pragma once
#include <gui.h>
#include <shapes.h>

/* bitmap header - 14 bytes */
struct s_bmp_header{
    int16 signature;
    int16 _;
    int16 fSize;
    int16 __, ___;
    int16 ____;
    int16 offset;
}packed;
typedef struct s_bmp_header bmp_header;


/* bitmap info header - 40 bytes */
struct s_info_header{
    int16 _;
    int16 size;
    int16 __;
    int16 width;
    int16 ___;
    int16 height;
    int16 ____;
    int16 _____;
    int16 ______, _______;
    int16 ________, _________;
    int16 __________, ___________;
    int16 ____________, _____________;
    int16 ______________, _______________;
}packed;
typedef struct s_info_header info_header;


/* bitmap color table - 4 * NumColors bytes */
struct s_rgb {
    int8 red;
    int8 green;
    int8 blue;
    int8 _;
}packed;
typedef struct s_rgb rgb;

typedef rgb color_table[16];
typedef point* bmp_line[MAXX]; /* several points in a line */

struct s_bitmap{
    int16 x, y; 
    bmp_header* hdr;
    info_header* info_hdr;
    color_table* colors;
    bmp_line lines[]; /* several lines */
}packed;

typedef struct s_bitmap bitmap;

bitmap* parsebmp(int8*);
boolean drawbmp(bitmap*, int16, int16);
bmp_line* bmppixeldata(int8*, int16, color_table*, int16 width, int16 height);
