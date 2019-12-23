#pragma once

#include "shared/utils/cubestr.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/protocol.h"
#include "shared/networking/frametimestate.h"

namespace shared {
    namespace network {
        static const int POLYHEDRON_PROTOCOL_VERSION        = 2;        // bump when protocol changes
        static const int POLYHEDRON_SERVER_PORT             = 42000;
        static const int POLYHEDRON_MASTER_PORT             = 41999;
        static const int POLYHEDRON_LANINFO_PORT            = 41998;
        static const int PROTOCOL_GAMEPLAYDEMO_VERSION      = 2;    // bump when demo format changes
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
        // Operator belongs to GameMode.
        inline shared::network::protocol::GameMode operator | (const shared::network::protocol::GameMode &a, const shared::network::protocol::GameMode &b) {
            return static_cast<shared::network::protocol::GameMode>((static_cast<int>(a) | static_cast<int>(b)));
        };

        //
        // IPMask struct.
        //
        struct IPMask {
            enet_uint32 ip, mask;

            void Parse(const char *name);
            int Print(char *buf) const;
            bool Check(enet_uint32 host) const { return (host & mask) == ip; }
        };

        // The put and get functions for packet buffers.
        extern void PutInt(ucharbuf &p, int n);
        extern void PutInt(packetbuf &p, int n);
        extern void PutInt(vector<uchar> &p, int n);
        extern int GetInt(ucharbuf &p);
        extern void PutUint(ucharbuf &p, int n);
        extern void PutUint(packetbuf &p, int n);
        extern void PutUint(vector<uchar> &p, int n);
        extern int GetUint(ucharbuf &p);
        extern void PutFloat(ucharbuf &p, float f);
        extern void PutFloat(packetbuf &p, float f);
        extern void PutFloat(vector<uchar> &p, float f);
        extern float GetFloat(ucharbuf &p);
        extern void SendCubeStr(const char *t, ucharbuf &p);
        extern void SendCubeStr(const char *t, packetbuf &p);
        extern void SendCubeStr(const char *t, vector<uchar> &p);
        extern void GetCubeStr(char *t, ucharbuf &p, size_t len);
        extern void PutMessage(ucharbuf &p, shared::network::protocol::Messages message); // Wraps up a PutInt, makes it clear we wanna send a message index

        // Templated versions, used for networking.
        template<size_t N> static inline void GetCubeStr(char (&t)[N], ucharbuf &p) { GetCubeStr(t, p, N); }
        template<size_t N> static inline void FilterText(char (&dst)[N], const char *src, bool whitespace = true, bool forcespace = false) { ::FilterText(dst, src, whitespace, forcespace, N-1); }

        // Client name and other related functionality.
        extern bool HasClientDuplicateName(entities::classes::BaseClientEntity *ce, const std::string &name);
    };    
};