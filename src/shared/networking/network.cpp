#include "shared/tools.h"
#include "shared/networking/network.h"
#include "shared/networking/cl_sv.h"

///////////////////////// network ///////////////////////
// all network traffic is in 32bit ints, which are then compressed using the following simple scheme (assumes that most values are small).
namespace networking {
    
    template<class T>
    static inline void putint_(T &p, int n)
    {
        if(n<128 && n>-127) p.put(n);
        else if(n<0x8000 && n>=-0x8000) { p.put(0x80); p.put(n); p.put(n>>8); }
        else { p.put(0x81); p.put(n); p.put(n>>8); p.put(n>>16); p.put(n>>24); }
    }
    void putint(ucharbuf &p, int n) { putint_(p, n); }
    void putint(packetbuf &p, int n) { putint_(p, n); }
    void putint(vector<uchar> &p, int n) { putint_(p, n); }
    void putint()
    int getint(ucharbuf &p)
    {
        int c = (char)p.get();
        if(c==-128) { int n = p.get(); n |= char(p.get())<<8; return n; }
        else if(c==-127) { int n = p.get(); n |= p.get()<<8; n |= p.get()<<16; return n|(p.get()<<24); }
        else return c;
    }

    // much smaller encoding for unsigned integers up to 28 bits, but can handle signed
    template<class T>
    static inline void putuint_(T &p, int n)
    {
        if(n < 0 || n >= (1<<21))
        {
            p.put(0x80 | (n & 0x7F));
            p.put(0x80 | ((n >> 7) & 0x7F));
            p.put(0x80 | ((n >> 14) & 0x7F));
            p.put(n >> 21);
        }
        else if(n < (1<<7)) p.put(n);
        else if(n < (1<<14))
        {
            p.put(0x80 | (n & 0x7F));
            p.put(n >> 7);
        }
        else
        {
            p.put(0x80 | (n & 0x7F));
            p.put(0x80 | ((n >> 7) & 0x7F));
            p.put(n >> 14);
        }
    }
    void putuint(ucharbuf &p, int n) { putuint_(p, n); }
    void putuint(packetbuf &p, int n) { putuint_(p, n); }
    void putuint(vector<uchar> &p, int n) { putuint_(p, n); }

    int getuint(ucharbuf &p)
    {
        int n = p.get();
        if(n & 0x80)
        {
            n += (p.get() << 7) - 0x80;
            if(n & (1<<14)) n += (p.get() << 14) - (1<<14);
            if(n & (1<<21)) n += (p.get() << 21) - (1<<21);
            if(n & (1<<28)) n |= ~0U<<28;
        }
        return n;
    }

    template<class T>
    static inline void putfloat_(T &p, float f)
    {
        lilswap(&f, 1);
        p.put((uchar *)&f, sizeof(float));
    }
    void putfloat(ucharbuf &p, float f) { putfloat_(p, f); }
    void putfloat(packetbuf &p, float f) { putfloat_(p, f); }
    void putfloat(vector<uchar> &p, float f) { putfloat_(p, f); }

    float getfloat(ucharbuf &p)
    {
        float f;
        p.get((uchar *)&f, sizeof(float));
        return lilswap(f);
    }

    template<class T>
    static inline void sendcubestr_(const char *t, T &p)
    {
        while(*t) putint(p, *t++);
        putint(p, 0);
    }
    void sendcubestr(const char *t, ucharbuf &p) { sendcubestr_(t, p); }
    void sendcubestr(const char *t, packetbuf &p) { sendcubestr_(t, p); }
    void sendcubestr(const char *t, vector<uchar> &p) { sendcubestr_(t, p); }

    void getcubestr(char *text, ucharbuf &p, size_t len)
    {
        char *t = text;
        do
        {
            if(t>=&text[len]) { text[len-1] = 0; return; }
            if(!p.remaining()) { *t = 0; return; }
            *t = getint(p);
        }
        while(*t++);
    }

    void ipmask::parse(const char *name)
    {   
        union { uchar b[sizeof(enet_uint32)]; enet_uint32 i; } ipconv, maskconv;
        ipconv.i = 0;
        maskconv.i = 0;
        loopi(4)
        {
            char *end = NULL;
            int n = strtol(name, &end, 10);
            if(!end) break;
            if(end > name) { ipconv.b[i] = n; maskconv.b[i] = 0xFF; }
            name = end; 
            while(int c = *name)
            {
                ++name; 
                if(c == '.') break;
                if(c == '/')
                {
                    int range = clamp(int(strtol(name, NULL, 10)), 0, 32);
                    mask = range ? ENET_HOST_TO_NET_32(0xFFffFFff << (32 - range)) : maskconv.i;
                    ip = ipconv.i & mask;
                    return;
                }
            }
        }
        ip = ipconv.i;
        mask = maskconv.i;
    }

    int ipmask::print(char *buf) const
    {
        char *start = buf;
        union { uchar b[sizeof(enet_uint32)]; enet_uint32 i; } ipconv, maskconv;
        ipconv.i = ip;
        maskconv.i = mask;
        int lastdigit = -1;
        loopi(4) if(maskconv.b[i])
        {
            if(lastdigit >= 0) *buf++ = '.';
            loopj(i - lastdigit - 1) { *buf++ = '*'; *buf++ = '.'; }
            buf += sprintf(buf, "%d", ipconv.b[i]);
            lastdigit = i;
        }
        enet_uint32 bits = ~ENET_NET_TO_HOST_32(mask);
        int range = 32;
        for(; (bits&0xFF) == 0xFF; bits >>= 8) range -= 8;
        for(; bits&1; bits >>= 1) --range;
        if(!bits && range%8) buf += sprintf(buf, "/%d", range);
        return int(buf-start);
    }
};