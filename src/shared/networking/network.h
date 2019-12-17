#pragma once

#include "shared/utils/cubestr.h"

namespace game {
    namespace networking {
        static const int POLYHEDRON_PROTOCOL_VERSION    = 2;       // bump when protocol changes
        static const int POLYHEDRON_SERVER_PORT         = 42000;
        static const int POLYHEDRON_MASTER_PORT         = 41999;
        static const int POLYHEDRON_LANINFO_PORT        = 41998;
        static const int PROTOCOL_GAMEPLAYDEMO_VERSION      = 2;       // bump when demo format changes
        static const char PROTOCOL_GAMEPLAYDEMO_MAGIC[16]   = "POLYHEDRONDEMO\0";

        //
        // ServerInfo
        //
        struct ServerInfo {
            cubestr name;
            cubestr map;
            cubestr desc;
            int protocol = INT_MIN;
            int numberOfPlayers = 0;
            int maxPlayers = 0;
            int ping = 0;
            vector<int> attr;
        };

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

        //
        // IPMask struct.
        //
        struct IPMask {
            enet_uint32 ip, mask;

            void parse(const char *name);
            int print(char *buf) const;
            bool check(enet_uint32 host) const { return (host & mask) == ip; }
        };

        // The put and get functions for packet buffers.
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

        // Templated versions, used for networking.
        template<size_t N> static inline void getcubestr(char (&t)[N], ucharbuf &p) { getcubestr(t, p, N); }
        template<size_t N> static inline void filtertext(char (&dst)[N], const char *src, bool whitespace = true, bool forcespace = false) { ::filtertext(dst, src, whitespace, forcespace, N-1); }

        // Operator belongs to mah mufuckin' thingy.
        inline networking::GameMode operator | (const game::networking::GameMode &a, const game::networking::GameMode &b) {
            return static_cast<game::networking::GameMode>((static_cast<int>(a) | static_cast<int>(b)));
        };

        
    };    
};