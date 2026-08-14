/* shapes.h */

#pragma once
#include <gui.h>

#define MAXX 40
#define MAXY 25
#define TEXT40x25 0x0

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
};
typedef struct s_line line;

void videomode(int8);
int8 getmaxx(void);
int8 getmaxy(void);
boolean drawpoint(point*);
boolean drawline(line*);

/* constructors */
point* mkpoint(int16, int16, int8);
line* mkline(point*, point*, int8, int8);

