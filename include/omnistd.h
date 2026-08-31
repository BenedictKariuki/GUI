/* omnistd.h */

#pragma once
#include <gui.h>

#define BUF_SIZE 256

#define MIN(x, y) ((x) < (y)) ? (x) : (y)

#define PEEK(x)                              \
    if (bytes > (MIN(BUF_SIZE, size) - (x))) \
    {                                        \
        isContinuing = false;                \
        break;                               \
    }

#define ZERO(x, y) set((x), 0, (y))
#define COPY(dst, src, size) memorycopy(dst, src, size, false)
#define STRINGCOPY(dst, src, size) memorycopy(dst, src, size, true)

void set(int8 *, int8, int16);
void memorycopy(int8 *, int8 *, int16, boolean isString);
int8 *snprintf(int8 *, int16, int8 *, ...);
int8 *int2hex(int16);
int16 stringlen(int8 *);