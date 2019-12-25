
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
        extern void ServerInit();
        extern void ServerUpdate();

        //
        // ClientInfo functionality.
        //
        extern void *NewClientInfo();
        extern void DeleteClientInfo(void *ci);
        
        // Number of 
        extern int ReserveClients();
        extern int NumberOfChannels(); // Client channels? 
        extern bool AllowBroadcast(int n);

        //
        // Server status functionality. (Paused, time etc)
        //
        extern bool IsPaused();
        extern int ScaleTime(int t);

        //
        // Packet management. 
        //
        extern void ParsePacket(int sender, int chan, packetbuf &p);
        extern void SendServerMessage(const char *s);
        extern bool SendPackets(bool force);
        extern void ServerInfoReply(ucharbuf &req, ucharbuf &p);
        extern bool ServerCompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np);

        //
        // Demo Packet management(So I assume)
        //
        extern void RecordPacket(int chan, void *data, int len);

        //
        // Client connect and Disconnect.
        //
        extern shared::network::protocol::DisconnectReason ClientDisconnect(int n);
        extern shared::network::protocol::DisconnectReason ClientConnect(int n, uint ip); // Returns Default aka None when properly connected.

        //
        // Port/default information functionality.
        //
        extern int ProtocolVersion();
        extern int ServerInfoPort(int servport);
        extern int ServerPort();
        extern int LanInfoPort();
        extern int MasterPort();
        extern const char *DefaultMaster();

        //
        // Master functionality.
        //
        extern void ProcessMasterInput(const char *cmd, int cmdlen, const char *args);
        extern void MasterConnected();
        extern void MasterDisconnected();
    };
};
