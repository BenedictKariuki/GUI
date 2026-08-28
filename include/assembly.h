/* assembly.h */
#pragma once
#include <gui.h>

void bputchar(int8);
void bvideomode(int8);
int16 bgetchar(void);
boolean bdrawpointT(int16, int16);
boolean bdrawpoint(int16, int16, int8);
void bclose(int16);
int16 bopen(int8 *);
int8 bread(int16);
int16 bmove(int16, int16);
