#include "../tools.h"

void filtertext(char *dst, const char *src, bool whitespace, bool forcespace, size_t len)
{
    for(int c = uchar(*src); c; c = uchar(*++src))
    {
        if(c == '\f')
        {
            if(!*++src) break;
            continue;
        }
        if(!iscubeprint(c))
        {
            if(!iscubespace(c) || !whitespace) continue;
            if(forcespace) c = ' ';
        }
        *dst++ = c;
        if(!--len) break;
    }
    *dst = '\0';
}

static cubestr tmpstr[4];
static int tmpidx = 0;

char *tempformatcubestr(const char *fmt, ...)
{
    tmpidx = (tmpidx+1)%4;

    va_list v;
    va_start(v, fmt);
    vformatcubestr(tmpstr[tmpidx], fmt, v);
    va_end(v);

    return tmpstr[tmpidx];
}