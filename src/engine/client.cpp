// client.cpp, mostly network related client game code

#include "engine.h"
#include "shared/networking/protocol.h"
#include "game/client/client.h"
#include "game/server/server.h"

struct ClientConnection {
    ENetHost *clientHost = NULL;
    ENetPeer *currentPeer = NULL, *connectedPeer = NULL;

    int connectedMilliseconds = 0;
    int connectionAttempts = 0;
    int disconnectMilliseconds = 0;
} clientConnection;

bool Multiplayer(bool msg)
{
    bool val = clientConnection.currentPeer || game::networking::HasNonLocalClients();
    if(val && msg) conoutf(CON_ERROR, "operation not available in Multiplayer");
    return val;
}

void setrate(int rate)
{
   if(!clientConnection.currentPeer) return;
   enet_host_bandwidth_limit(clientConnection.clientHost, rate*1024, rate*1024);
}

VARF(rate, 0, 0, 1024, setrate(rate));

void throttle();

VARF(throttle_interval, 0, 5, 30, throttle());
VARF(throttle_accel,    0, 2, 32, throttle());
VARF(throttle_decel,    0, 2, 32, throttle());

void throttle()
{
    if(!clientConnection.currentPeer) return;
    ASSERT(ENET_PEER_PACKET_THROTTLE_SCALE==32);
    enet_peer_throttle_configure(clientConnection.currentPeer, throttle_interval*1000, throttle_accel, throttle_decel);
}

bool IsConnected(bool attempt, bool local)
{
    return clientConnection.currentPeer || (attempt && clientConnection.connectedPeer) || (local && game::networking::HasLocalClients());
}

SCRIPTEXPORT_AS(IsConnected) void IsConnected_scriptimpl(CommandTypes::Boolean attempt, CommandTypes::Boolean local)
{
    intret(IsConnected(*attempt > 0, *local != 0) ? 1 : 0);
}

const ENetAddress *ConnectedPeer()
{
    return clientConnection.currentPeer ? &clientConnection.currentPeer->address : NULL;
}

SCRIPTEXPORT_AS(connectedip) void ConnectedIP()
{
    const ENetAddress *address = ConnectedPeer();
    cubestr hostname;
    result(address && enet_address_get_host_ip(address, hostname, sizeof(hostname)) >= 0 ? hostname : "");
};

SCRIPTEXPORT_AS(connectedport) void connectedport()
{
    const ENetAddress *address = ConnectedPeer();
    intret(address ? address->port : -1);
};

void AbortConnect()
{
    if(!clientConnection.connectedPeer) return;
    game::ConnectFail();
    if(clientConnection.connectedPeer->state!=ENET_PEER_STATE_DISCONNECTED) enet_peer_reset(clientConnection.connectedPeer);
    clientConnection.connectedPeer = NULL;
    if(clientConnection.currentPeer) return;
    enet_host_destroy(clientConnection.clientHost);
    clientConnection.clientHost = NULL;
}

SVARP(connectname, "");
VARP(connectport, 0, 0, 0xFFFF);

SCRIPTEXPORT_AS(connect) void ConnectServ(const char *serverName, int serverPort, const char *serverPassword)
{
    if(clientConnection.connectedPeer)
    {
        conoutf("aborting connection attempt");
        AbortConnect();
    }

    if(serverPort <= 0) serverPort = game::server::ServerPort();

    ENetAddress address;
    address.port = serverPort;

    if(serverName)
    {
        if(strcmp(serverName, connectname)) setsvar("connectname", serverName);
        if(serverPort != connectport) setvar("connectport", serverPort);
        AddServer(serverName, serverPort, serverPassword && serverPassword[0] ? serverPassword : NULL);
        conoutf("attempting to connect to %s:%d", serverName, serverPort);
        if(!ResolverWait(serverName, &address))
        {
            conoutf("\f3could not resolve server %s", serverName);
            return;
        }
    }
    else
    {
        setsvar("connectname", "");
        setvar("connectport", 0);
        conoutf("attempting to connect over LAN");
        address.host = ENET_HOST_BROADCAST;
    }

    if(!clientConnection.clientHost)
    {
        clientConnection.clientHost = enet_host_create(NULL, 2, game::server::GetNumChannels(), rate*1024, rate*1024);
        if(!clientConnection.clientHost)
        {
            conoutf("\f3could not connect to server");
            return;
        }
        clientConnection.clientHost->duplicatePeers = 0;
    }

    clientConnection.connectedPeer = enet_host_connect(clientConnection.clientHost, &address, game::server::GetNumChannels(), 0);
    enet_host_flush(clientConnection.clientHost);
    clientConnection.connectedMilliseconds = ftsClient.totalMilliseconds;
    clientConnection.connectionAttempts = 0;

    game::ConnectAttempt(serverName ? serverName : "", serverPassword ? serverPassword : "", address);
}

SCRIPTEXPORT_AS(reconnect) void Reconnect(const char *serverPassword)
{
    if(!connectname[0] || connectport <= 0)
    {
        conoutf(CON_ERROR, "no previous connection");
        return;
    }

    ConnectServ(connectname, connectport, serverPassword);
}

void Disconnect(bool async, bool cleanup)
{
    if(clientConnection.currentPeer)
    {
        if(!clientConnection.disconnectMilliseconds)
        {
            enet_peer_disconnect(clientConnection.currentPeer, DISC_NONE);
            enet_host_flush(clientConnection.clientHost);
            clientConnection.disconnectMilliseconds = ftsClient.totalMilliseconds;
        }
        if(clientConnection.currentPeer->state!=ENET_PEER_STATE_DISCONNECTED)
        {
            if(async) return;
            enet_peer_reset(clientConnection.currentPeer);
        }
        clientConnection.currentPeer = NULL;
        clientConnection.disconnectMilliseconds = 0;
        conoutf("dIsConnected");
        game::client::GameDisconnect(cleanup);
        mainmenu = 1;
    }
    if(!clientConnection.connectedPeer && clientConnection.clientHost)
    {
        enet_host_destroy(clientConnection.clientHost);
        clientConnection.clientHost = NULL;
    }
}

void TryDisconnect(bool local)
{
    if(clientConnection.connectedPeer)
    {
        conoutf("aborting connection attempt");
        AbortConnect();
    }
    else if(clientConnection.currentPeer)
    {
        conoutf("attempting to disconnect...");
        Disconnect(true, !clientConnection.disconnectMilliseconds);
    }
    else if(local && game::networking::HasLocalClients()) LocalDisconnect();
    else conoutf("not connected");
}

SCRIPTEXPORT_AS(lanconnect) void LanConnect(int *port, char *pw)
{
    ConnectServ(NULL, *port, pw);
}

SCRIPTEXPORT_AS(disconnect) void disconnect_scriptimpl(int *local)
{
    TryDisconnect(*local != 0);
}

SCRIPTEXPORT_AS(localconnect) void localconnect_scriptimpl() //!!!!
{
    if(!game::networking::IsConnected())
    {
        game::networking::LocalConnect();
    }
}

SCRIPTEXPORT_AS(localdisconnect) void LocalDisconnect_scriptimpl()
{
    if(game::networking::HasLocalClients())
    {
        LocalDisconnect();
    }
}

void SendClientPacket(ENetPacket *packet, int chan)
{
    if(clientConnection.currentPeer) enet_peer_send(clientConnection.currentPeer, chan, packet);
    else LocalClientToServer(chan, packet);
}

void FlushClient()
{
    if(clientConnection.clientHost) enet_host_flush(clientConnection.clientHost);
}

void NetErr(const char *s, bool disc)
{
    conoutf(CON_ERROR, "\f3illegal network message (%s)", s);
    if(disc) game::networking::Disconnect();
}

void LocalServerToClient(int chan, ENetPacket *packet)   // processes any updates from the server
{
    packetbuf p(packet);
    game::ParsePacketclient(chan, p);
}

void ClientKeepAlive() { if(clientConnection.clientHost) enet_host_service(clientConnection.clientHost, NULL, 0); }

void GetS2C()           // get updates from the server
{
    ENetEvent event;
    if(!clientConnection.clientHost) return;
    if(clientConnection.connectedPeer && ftsClient.totalMilliseconds/3000 > clientConnection.connectedMilliseconds/3000)
    {
        conoutf("attempting to connect...");
        clientConnection.connectedMilliseconds = ftsClient.totalMilliseconds;
        ++clientConnection.connectionAttempts;
        if(clientConnection.connectionAttempts > 3)
        {
            conoutf("\f3could not connect to server");
            AbortConnect();
            return;
        }
    }
    while(clientConnection.clientHost && enet_host_service(clientConnection.clientHost, &event, 0)>0)
    switch(event.type)
    {
        case ENET_EVENT_TYPE_CONNECT:
            Disconnect(false, false);
            LocalDisconnect(false);
            clientConnection.currentPeer = clientConnection.connectedPeer;
            clientConnection.connectedPeer = NULL;
            conoutf("connected to server");
            throttle();
            if(rate) setrate(rate);
            game::client::GameConnect(true);
            break;

        case ENET_EVENT_TYPE_RECEIVE:
            if(clientConnection.disconnectMilliseconds) conoutf("attempting to disconnect...");
            else LocalServerToClient(event.channelID, event.packet);
            enet_packet_destroy(event.packet);
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            if(event.data>=DISC_NUM) event.data = static_cast<enet_uint32>(game::networking::protocol::DisconnectReason::Default);
            if(event.peer==clientConnection.connectedPeer)
            {
                conoutf("\f3could not connect to server");
                AbortConnect();
            }
            else
            {
                if(!clientConnection.disconnectMilliseconds || event.data)
                {
                    const char *msg = game::networking::DisconnectReason(static_cast<game::networking::protocol::DisconnectReason>(event.data));
                    if(msg) conoutf("\f3server network error, disconnecting (%s) ...", msg);
                    else conoutf("\f3server network error, disconnecting...");
                }
                game::networking::Disconnect();
            }
            return;

        default:
            break;
    }
}


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
#if 0
#include "/Users/micha/dev/ScMaMike/src/build/binding/..+engine+client.binding.cpp"
#endif
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
