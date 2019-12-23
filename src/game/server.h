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
    void *newclientinfo();
    void deleteclientinfo(void *ci);
    void serverinit();
    int reserveclients();
    int numchannels();
    void clientdisconnect(int n);
    int clientconnect(int n, uint ip);
    void localdisconnect(int n);
    void localconnect(int n);
    bool allowbroadcast(int n);
    void recordpacket(int chan, void *data, int len);
    void parsepacket(int sender, int chan, packetbuf &p);
    void sendservmsg(const char *s);
    bool sendpackets(bool force);
    void serverinforeply(ucharbuf &req, ucharbuf &p);
    void serverupdate();
    bool servercompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np);

    int protocolversion();
    int serverinfoport(int servport);
    int serverport();
    const char *defaultmaster();
    int masterport();
    int laninfoport();
    void processmasterinput(const char *cmd, int cmdlen, const char *args);
    void masterconnected();
    void masterdisconnected();
    bool ispaused();
    int scaletime(int t);
};