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

int16 getmaxx(){
    return MAXX;
}

int16 getmaxy(){
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
    pt->color = color;
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
    bdrawpoint(pt->x, pt->y, pt->color);
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
        maxy = ln->pt2->y + ln->thickness;
        if(maxx > scr_maxx)
            maxx = scr_maxx;
        if(maxy > scr_maxy)
            maxy = scr_maxy;
        for(y=starty; y<maxy; y++){
            for(x=startx; x<maxx; x++){
                pt = mkpoint(x,y,ln->color);
                if(pt)
                    drawpoint(pt);
            }
        }
    }
    else if(ln->pt1->y == ln->pt2->y){
        starty = ln->pt1->y;
        maxy = (ln->pt1->y + ln->thickness);
        startx = ln->pt1->x;
        maxx = ln->pt2->x + ln->thickness;
        if(maxy > scr_maxy)
            maxy = scr_maxy;
        if(maxx > scr_maxx)
            maxx = scr_maxx;
        for(x=startx; x<maxx; x++){
            for(y=starty; y<maxy; y++){
                pt = mkpoint(x,y,ln->color);
                if(pt)
                    drawpoint(pt);
            }
        }
    }

    else
        return false;

    return true;
}

rectangle* mkrectangle(point* pt1, point* pt2, int8 fgcolor, int8 bgcolor, int16 thickness, boolean solid){
    rectangle* rect;
    int16 size;
    if(!pt1 || !pt2)
        return (rectangle*)0;
    size = sizeof(struct s_rectangle);
    rect = (rectangle*)alloc(size);
    if(!rect)
        return (rectangle*)0; 
    rect->pt1 = pt1;
    rect->pt2 = pt2;
    rect->fgcolor = fgcolor;
    rect->bgcolor = bgcolor;
    rect->thickness = thickness;
    rect->flags = FL_NONE;
    if(solid)
        rect->flags |= FL_SOLID;
    return rect;
}

boolean drawrectangle(rectangle* rect){
    int16 maxx, maxy;
    point* pt3, *pt4;
    maxx = getmaxx();
    maxy = getmaxy();
    if(!videoinit)
        return false;
    if(!rect)
        return false;
    if((rect->pt1->x > maxx) || (rect->pt1->y > maxy))
        return false;
    if((rect->pt2->x < rect->pt1->x) || (rect->pt2->y < rect->pt1->y))
        return false;

    pt3 = mkpoint(rect->pt2->x, rect->pt1->y, rect->fgcolor);
    pt4 = mkpoint(rect->pt1->x, rect->pt2->y, rect->fgcolor);
    
    line* top, *left, *bottom, *right;
    top = mkline(rect->pt1, pt3, rect->fgcolor, rect->thickness);
    left = mkline(rect->pt1, pt4, rect->fgcolor, rect->thickness);
    bottom = mkline(pt4, rect->pt2, rect->fgcolor, rect->thickness);
    right = mkline(pt3, rect->pt2, rect->fgcolor, rect->thickness);
    drawline(top);
    drawline(left);
    drawline(bottom);
    drawline(right);
    return true;
}
