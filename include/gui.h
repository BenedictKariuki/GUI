/* gui.h */

#pragma once

#define $1 (int8*)
#define $2 (int16*)
#define $v (void*)
#define true 1
#define false 0

#define packed __attribute__((packed)) /* this syntax is specific to gcc */

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned char boolean;

extern int8 heap;

void print(int8*);
void putchar(int8);
void* alloc(int16);
void freeall(void);
void videomode(int8);
int8 getchar(void);
