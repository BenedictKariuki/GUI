/* shapes.h */

#pragma once
#include <gui.h>

#define MAXX 640
#define MAXY 480
#define BTEXT40x25 0x00
#define BGFX640x480 0x12

#define FL_NONE 0x00
#define FL_SOLID 0x01

/* A data structure representing a pixel. Each pixel will be able to display 
** 16 different colors. Therefore, the color property will only need 4 bits, 
** so we need a bit field.
*/
struct s_point{
    int16 x, y;
    int8 color : 4;
} packed;

typedef struct s_point point;


/* A data structure representing a line. We need two points to draw a line.
*/
struct s_line{
    point* pt1, *pt2;
    int8 color: 4;
    int8 thickness;
} packed;
typedef struct s_line line;


/* A data structure representing a rectangle. */
struct s_rectangle{
    point* pt1, *pt2;
    int8 fgcolor: 4;
    int8 bgcolor: 4;
    int16 thickness;
    int8 flags: 4;
} packed;
typedef struct s_rectangle rectangle;


void videomode(int8);
int16 getmaxx(void);
int16 getmaxy(void);
boolean drawpoint(point*);
boolean drawline(line*);
boolean drawrectangle(rectangle*);

/* constructors */
point* mkpoint(int16, int16, int8);
line* mkline(point*, point*, int8, int8);
rectangle* mkrectangle(point*, point*, int8, int8, int16, boolean);

