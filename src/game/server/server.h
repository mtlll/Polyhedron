#pragma once

#include "cube.h"
#include "shared/networking/network.h"
#include "shared/networking/cl_sv.h"

namespace game {
    
    namespace server
    {
        // Server time related functions
        extern void ServerInit();
        extern bool IsPaused();
        extern int ScaleTime(int t);
        extern void ServerUpdate();

        // Server client related functions.
        extern void *NewClientInfo();
        extern void DeleteClientInfo(void *ci);
        extern int ReserveClients();
        extern void ClientDisconnect(int n);
        extern int ClientConnect(int n, uint ip);
        extern void LocalDisconnect(int n);
        extern void LocalConnect(int n);

        // Broadcasting related functions.
        extern bool AllowBroadcast(int n);
        extern void RecordPacket(int chan, void *data, int len);
        extern void ParsePacket(int sender, int chan, packetbuf &p);
        extern void SendServMsg(const char *s);
        extern bool SendPackets(bool force);
        extern void ServerInfoReply(ucharbuf &req, ucharbuf &p);
        extern int GetNumChannels();
        
        // Protocol related functions.
        extern int ProtocolVersion();
        extern int serverinfoport(int servport);
        extern int ServerPort();
        extern int MasterPort();
        extern int LanInfoPort();

        // Master server related functions.
        extern const char *DefaultMaster();
        extern void ProcessMasterInput(const char *cmd, int cmdlen, const char *args);
        extern void MasterConnected();
        extern void MasterDisconnected();
        extern void ConnectMaster();

        // Are servers compatible?
        extern bool servercompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np);

        extern int MsgSizeLookUp(int msg);
    } // server
} // game