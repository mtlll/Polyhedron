
#pragma once

#include "shared/tools.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/protocol.h"
#include "shared/networking/cl_frametimestate.h"
#include "shared/networking/sv_frametimestate.h"

namespace game {
    namespace server {
        // Externize it.
        extern shared::network::ServerFrameTimeState ftsServer;

        // Neatly ordered into a struct for variable svClients.       
        struct ServerClients {
            vector<shared::network::ClientInfo *> connected;
            vector<shared::network::ClientInfo *> clients;
            vector<shared::network::ClientInfo *> bots;
        }; extern ServerClients svClients;

        SVAR(serverauth, "");
        struct ServInfo
        {
            cubestr name, map, desc;
            int protocol;
            int numberOfPlayers, maximumOfPlayers, ping;
            vector<int> attr;

            ServInfo() : protocol(INT_MIN), numberOfPlayers(0), maximumOfPlayers(0)
            {
                name[0] = map[0] = desc[0] = '\0';
            }
        };

        extern ServInfo *GetServInfo(int i);

        #define GETSERVINFO(idx, si, body) do { \
            ServInfo *si = GetServInfo(idx); \
            if(si) \
            { \
                body; \
            } \
        } while(0)
        #define GETSERVINFOATTR(idx, aidx, aval, body) \
            GETSERVINFO(idx, si, { if(si->attr.inrange(aidx)) { int aval = si->attr[aidx]; body; } })

        //
        // Server init, uupdate etc functions.
        //
        void ServerInit();
        void ServerUpdate();
        void ServerInfoReply(ucharbuf &req, ucharbuf &p);
        bool ServerCompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np);

        //
        // Client connect and Disconnect functions.
        //
        shared::network::protocol::DisconnectReason ClientDisconnect(int n);
        shared::network::protocol::DisconnectReason ClientConnect(int n, uint ip); // Returns Default aka None when properly connected.
	
        void LocalDisconnect(int n);
		void LocalConnect(int n);
    

        //
        // ClientInfo functionality.
        //
        void *NewClientInfo();
        void DeleteClientInfo(void *ci);
		int ReserveClients();
        
        //
        // General functions. 
        //
        int NumberOfChannels(); // Client channels? 
        bool AllowBroadcast(int n);

        //
        // Server status functionality. (Paused, time etc)
        //
        bool IsPaused();
        int ScaleTime(int t);

        //
        // Packet management. 
        //
        void ParsePacket(int sender, int chan, packetbuf &p);
        void SendServerMessage(const char *s);
        void SendServInfo(shared::network::ClientInfo *ci);
        bool SendPackets(bool force = false);
        
        
        //
        // Demo Packet management(So I assume)
        //
        extern void RecordPacket(int chan, void *data, int len);

        //
        // Information functionality.
        //
        int ProtocolVersion();
        int ServerInfoPort(int servport);
        int ServerPort();
        int LanInfoPort();
        int MasterPort();
        const char *DefaultMaster();

        //
        // Master functionality.
        //
        void ProcessMasterInput(const char *cmd, int cmdlen, const char *args);
        void MasterConnected();
        void MasterDisconnected();
    };
};
