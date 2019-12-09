#pragma once

namespace game {
    namespace networking {
        //
        // Enum Class copy of GameMode flags.
        //
        enum struct GameMode : int {
            Team       = 1<<0,
            Ctf        = 1<<1,
            OverTime   = 1<<2,
            Edit       = 1<<3,
            Demo       = 1<<4,
            Local      = 1<<5,
            Lobby      = 1<<6,
            Rail       = 1<<7,
            Pulse      = 1<<8
        };

        inline game::networking::GameMode operator | (const game::networking::GameMode &a, const game::networking::GameMode &b) {
            return static_cast<game::networking::GameMode>((static_cast<int>(a) | static_cast<int>(b)));
        };


        // Networked versions of.
        template<size_t N> static inline void getcubestr(char (&t)[N], ucharbuf &p) { game::networking::getcubestr(t, p, N); }
        template<size_t N> static inline void filtertext(char (&dst)[N], const char *src, bool whitespace = true, bool forcespace = false) { game::networking::filtertext(dst, src, whitespace, forcespace, N-1); }

         //
        // IPMask struct.
        //
        struct ipmask
        {
            enet_uint32 ip, mask;

            void parse(const char *name);
            int print(char *buf) const;
            bool check(enet_uint32 host) const { return (host & mask) == ip; }
        };

        extern void putint(ucharbuf &p, int n);
        extern void putint(packetbuf &p, int n);
        extern void putint(vector<uchar> &p, int n);
        extern int getint(ucharbuf &p);
        extern void putuint(ucharbuf &p, int n);
        extern void putuint(packetbuf &p, int n);
        extern void putuint(vector<uchar> &p, int n);
        extern int getuint(ucharbuf &p);
        extern void putfloat(ucharbuf &p, float f);
        extern void putfloat(packetbuf &p, float f);
        extern void putfloat(vector<uchar> &p, float f);
        extern float getfloat(ucharbuf &p);
        extern void sendcubestr(const char *t, ucharbuf &p);
        extern void sendcubestr(const char *t, packetbuf &p);
        extern void sendcubestr(const char *t, vector<uchar> &p);
        extern void getcubestr(char *t, ucharbuf &p, size_t len);
    };    
};