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
    };
};

namespace server
{
    void *NewClientInfo();
    void DeleteClientInfo(void *ci);
    void ServerInit();
    int ReserveClients();
    int NumChannels();
    extern shared::network::protocol::DisconnectReason ClientDisconnect(int n);
    extern shared::network::protocol::DisconnectReason ClientConnect(int n, uint ip); // Returns Default aka None when properly connected.
    void LocalDisconnect(int n);
    void LocalConnect(int n);
    bool AllowBroadcast(int n);
    void RecordPacket(int chan, void *data, int len);
    void ParsePacket(int sender, int chan, packetbuf &p);
    void SendServerMessage(const char *s);
    bool SendPackets(bool force);
    void ServerInfoReply(ucharbuf &req, ucharbuf &p);
    void ServerUpdate();
    bool ServerCompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np);

    int ProtocolVersion();
    int ServerInfoPort(int servport);
    int ServerPort();
    const char *DefaultNaster();
    int MasterPort();
    int LanInfoPort();
    void ProcessMasterInput(const char *cmd, int cmdlen, const char *args);
    void MasterConnected();
    void MasterDisconnected();
    bool IsPaused();
    int ScaleTime(int t);
};