#pragma once
#include "../game.h"

namespace server
{
    struct ClientInfo {
        // Client and Owner number.
		int clientNumber = 0;           // Client number.
        int ownerNumber = 0;            // Owner client number.
        int connectMilliseconds = 0;    // Connection MS duration.

        int sessionID = 0;              // ENET Peer Session ID.
        int overflow = 0;               // Overflow??

        int playerModelID = 0;            // PLayer Model ID.
        
        // Client personal relations.
        cubestr name;
        int privilege;
        bool local = false;
        bool connected = false;
        
        // Time related.
        bool timeSync = false;
        int gameOffset = 0;
        int lastEvent = 0;
        int pushed = 0;
        int exceeded = 0;
	};

    // Server time related functions
    void ServerInit();
    bool ispaused();
    int scaletime(int t);
    void ServerUpdate();

    // Server client related functions.
    void *NewClientInfo();
    void DeleteClientInfo(void *ci);
    int ReserveClients();
    void ClientDisconnect(int n);
    int ClientConnect(int n, uint ip);
    void LocalDisconnect(int n);
    void localconnect(int n);

    // Broadcasting related functions.
    bool AllowBroadcast(int n);
    void RecordPacket(int chan, void *data, int len);
    void ParsePacket(int sender, int chan, packetbuf &p);
    void sendservmsg(const char *s);
    bool SendPackets(bool force);
    void ServerInfoReply(ucharbuf &req, ucharbuf &p);
    int GetGetNumChannels();
    
    // Protocol related functions.
    int ProtocolVersion();
    int serverinfoport(int servport);
    int ServerPort();
    int MasterPort();
    int LanInfoPort();

    // Master server related functions.
    const char *DefaultMaster();
    void processmasterinput(const char *cmd, int cmdlen, const char *args);
    void masterconnected();
    void masterdisconnected();

    // Are servers compatible?
    bool servercompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np);
}