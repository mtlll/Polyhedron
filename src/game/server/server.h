
#pragma once

#include "shared/tools.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/protocol.h"
#include "shared/networking/frametimestate.h"

namespace game {
    namespace server {
        //
        // Neatly ordered into a struct for variable svClients.
        //
        struct ServerClients {
            vector<shared::network::ClientInfo *> connected;
            vector<shared::network::ClientInfo *> clients;
            vector<shared::network::ClientInfo *> bots;
        }; extern ServerClients svClients;

        //
        // Server initializing and shutdown
        //
        void ServerInit();
        void ServerUpdate();

        //
        // ClientInfo functionality.
        //
        void *NewClientInfo();
        void DeleteClientInfo(void *ci);
        
        // Number of 
        int ReserveClients();
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
        bool SendPackets(bool force);
        void ServerInfoReply(ucharbuf &req, ucharbuf &p);
        bool ServerCompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np);

        //
        // Demo Packet management(So I assume)
        //
        void RecordPacket(int chan, void *data, int len);

        //
        // Client connect and Disconnect.
        //
        void ClientDisconnect(int n);
        int ClientConnect(int n, uint ip);

        //
        // Port/default information functionality.
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
