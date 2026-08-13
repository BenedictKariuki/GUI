/* shapes.c */

#include <gui.h>
#include <assembly.h>
#include <shapes.h>

boolean videoinit;

void videomode(int8 mode){
    if(mode > 0x9f) return;
    bvideomode(mode);
    videoinit = true;
    return;
}

int8 getmaxx(){
    return MAXX;
}

int8 getmaxy(){
    return MAXY;
}

point* mkpoint(int16 x, int16 y){
    point* pt;
    int16 size;
    size = sizeof(struct s_point);
    pt = (point*)alloc(size);
    if(!pt) return (point*)0;
    pt->x = x;
    pt->y = y;
    return pt;
}

boolean drawpoint(point* pt){
    if(!videoinit) return false;
    if(!pt) return false;
    int16 maxx, maxy;
    maxx = getmaxx();
    maxy = getmaxy();
    if((pt->x > maxx) || (pt->y > maxy)) return false;
    bdrawpointT(pt->x, pt->y);
    return true;
}

