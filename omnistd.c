/* omnistd.c */

#include <gui.h>
#include <omnistd.h>

void memorycopy(int8 *dst, int8 *src, int16 size, boolean isString)
{
    int16 n;
    int8 *dst_ptr;
    int8 *src_ptr;

    for (n = 0, dst_ptr = dst, src_ptr = src; isString && *src_ptr && n < size; n++, dst_ptr++, src_ptr++)
    {
        *dst_ptr = *src_ptr;
    }
    return;
}

void set(int8 *dst, int8 c, int16 size)
{
    int16 n;
    int8 *ptr;

    for (n = 0, ptr = dst; n < size; n++, ptr++)
        *ptr = c;
    return;
}

int8 hexchar(int8 c)
{
    // putchar(c);
    if (c < 10)
    {

        return c + '0';
    }
    else if (c > 9)
    {

        return (c - 10) + 'a';
    }
}

int8 *int2hex(int16 x)
{
    int8 a, b, c, d, ahex, bhex, chex, dhex;
    int8 *ret;
    d = (x & 0x000f);
    c = (x & 0x00f0) >> 4;
    b = (x & 0x0f00) >> 8;
    a = (x & 0xf000) >> 12;

    dhex = hexchar(d);
    chex = hexchar(c);
    bhex = hexchar(b);
    ahex = hexchar(a);

    ret = $1 alloc(5);
    ret[0] = ahex;
    ret[1] = bhex;
    ret[2] = chex;
    ret[3] = dhex;
    ret[4] = 0;
    // print(ret);
    return ret;
}

int16 stringlen(int8 *str)
{
    if (!str)
        return 0;
    int16 len;
    int8 *ptr;

    len = 0;
    ptr = str;
    while (*ptr)
    {
        len++;
        ptr++;
    }
    return len;
}

int8 *snprintf(int8 *dst, int16 size, int8 *fmt, ...)
{
    int8 buf[BUF_SIZE];
    int16 bytes, argc, len;
    int8 *dst_ptr, *src_ptr, *p;
    int8 **p_ptr;
    int16 *ip;
    boolean isContinuing;

    if (!dst || !fmt)
        return $1 0;

    p_ptr = &fmt;

    ZERO($1(&buf), BUF_SIZE);
    bytes = argc = 0;
    src_ptr = fmt;
    dst_ptr = dst;
    isContinuing = true;

    while (*src_ptr && isContinuing)
    {
        switch (*src_ptr)
        {
        case '%':
            src_ptr++;
            switch (*src_ptr)
            {
            case 0:
                break;
            case 'c':
                PEEK(2);
                p = *++p_ptr;
                len = stringlen(p);

                if (len)
                {
                    STRINGCOPY($1 dst_ptr, $1 p, 1);
                    dst_ptr++;
                    src_ptr++;
                    bytes++;
                }

                break;
            case 's':
                p = *++p_ptr;
                len = stringlen(p);

                if (len)
                {
                    PEEK(len + 1);
                    STRINGCOPY($1 dst_ptr, $1 p, len);
                    dst_ptr += len;
                    bytes += len;
                }
                src_ptr++;
                break;
            case 'x':

                PEEK(5);
                ip = (int16 *)++p_ptr;
                p = int2hex(*ip);

                STRINGCOPY($1 dst_ptr, $1 p, 4);
                dst_ptr += 4;
                src_ptr++;
                bytes += 4;
                break;
            case '%':
                PEEK(2);
                *dst_ptr++ = '%';
                src_ptr++;
                bytes++;
                break;
            }
            break;

        case '\n':
            PEEK(3);
            *dst_ptr++ = '\r';
            *dst_ptr++ = '\n';
            src_ptr++;
            bytes += 2;
            break;

        default:
            PEEK(2);
            *dst_ptr++ = *src_ptr++;
            bytes++;
            break;
        }
    }
    *dst_ptr = 0;
    return dst;
}