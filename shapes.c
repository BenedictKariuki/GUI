/* shapes.c */

#include <gui.h>
#include <assembly.h>
#include <shapes.h>

boolean videoinit;

void videomode(int8 mode){
    if(mode > 0x9f) 
        return;
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

point* mkpoint(int16 x, int16 y, int8 color){
    point* pt;
    int16 size;
    size = sizeof(struct s_point);
    pt = (point*)alloc(size);
    if(!pt) 
        return (point*)0;
    pt->x = x;
    pt->y = y;
    return pt;
}

boolean drawpoint(point* pt){
    if(!videoinit) 
        return false;
    if(!pt) 
        return false;
    int16 maxx, maxy;
    maxx = getmaxx();
    maxy = getmaxy();
    if((pt->x > maxx) || (pt->y > maxy)) 
        return false;
    bdrawpointT(pt->x, pt->y);
    return true;
}

line* mkline(point* pt1, point* pt2, int8 color, int8 thickness){
    line* ln;
    int16 size;
    if(!pt1 || !pt2 || !thickness){     
        return (line*)0;
    }
    size = sizeof(struct s_line);
    ln = (line*)alloc(size);
    if(!ln) 
        return (line*)0;
    ln->pt1 = pt1;
    ln->pt2 = pt2;
    ln->color = color;
    ln->thickness = thickness;
    return ln;
}

boolean drawline(line* ln){
    if(!videoinit) 
        return false;
    if(!ln) 
        return false;

    point* pt;
    int16 maxx, maxy, scr_maxx, scr_maxy, startx, starty, x, y;
    scr_maxx = getmaxx();
    scr_maxy = getmaxy();

    /* direction
     * if x values equal, line is vertical.
     * if y values equal, line is horizontal.
     * else, diagonal (not support currently).
     * Note: Drawing the line backwards is not supported.
    */
    if((ln->pt1->x > ln->pt2->x) || (ln->pt1->y > ln->pt2->y))
        return false;
    
    if(ln->pt1->x == ln->pt2->x){
        startx = ln->pt1->x;
        maxx = (ln->pt1->x + ln->thickness);
        starty = ln->pt1->y;
        maxy = ln->pt2->y;
        if(maxx > scr_maxx)
            maxx = scr_maxx;
        if(maxy > scr_maxy)
            maxy = scr_maxy;
    }

    else if(ln->pt1->y == ln->pt2->y){
        starty = ln->pt1->y;
        maxy = (ln->pt1->y + ln->thickness);
        startx = ln->pt1->x;
        maxx = ln->pt2->x;
        if(maxy > scr_maxy)
            maxy = scr_maxy;
        if(maxx > scr_maxx)
            maxx = scr_maxx;
    }

    else
        return false;

    for(x=startx; x<maxx; x++){
        for(y=starty; y<maxy; y++){
            pt = mkpoint(x,y,ln->color);
            if(pt)
                drawpoint(pt);
        }
    }
    return true;
}
