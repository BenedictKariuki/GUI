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

void videomode(int8);
int8 getmaxx(void);
int8 getmaxy(void);
boolean drawpoint(point*);

/* constructors */
point* mkpoint(int16, int16);

