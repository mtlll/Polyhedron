// client.cpp, mostly network related client game code

#include "engine.h"

#include "game/game.h"
#include "game/client/client.h"
#include "game/server/server.h"

#include "shared/networking/network.h"
#include "shared/networking/protocol.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/cl_sv.h"

ENetHost *clienthost = NULL;
ENetPeer *curpeer = NULL, *connpeer = NULL;
int connmillis = 0, connattempts = 0, discmillis = 0;

bool Multiplayer(bool msg)
{
    bool val = curpeer || engine::server::HasNonLocalClients();
    if (val && msg)
        conoutf(CON_ERROR, "Operation not available in multiplayer");
    return val;
}

void setrate(int rate)
{
    if (!curpeer)
        return;
    enet_host_bandwidth_limit(clienthost, rate * 1024, rate * 1024);
}

VARF(rate, 0, 0, 1024, setrate(rate));

void throttle();

VARF(throttle_interval, 0, 5, 30, throttle());
VARF(throttle_accel, 0, 2, 32, throttle());
VARF(throttle_decel, 0, 2, 32, throttle());

void throttle()
{
    if (!curpeer)
        return;
    ASSERT(ENET_PEER_PACKET_THROTTLE_SCALE == 32);
    enet_peer_throttle_configure(curpeer, throttle_interval * 1000, throttle_accel, throttle_decel);
}

bool isconnected(bool attempt, bool local)
{
    return curpeer || (attempt && connpeer) || (local && engine::server::HasLocalClients());
}

SCRIPTEXPORT_AS(isconnected)
void isconnected_scriptimpl(CommandTypes::Boolean attempt, CommandTypes::Boolean local)
{
    intret(isconnected(*attempt > 0, *local != 0) ? 1 : 0);
}

const ENetAddress *connectedpeer()
{
    return curpeer ? &curpeer->address : NULL;
}

SCRIPTEXPORT void connectedip()
{
    const ENetAddress *address = connectedpeer();
    cubestr hostname;
    result(address && enet_address_get_host_ip(address, hostname, sizeof(hostname)) >= 0 ? hostname : "");
};

SCRIPTEXPORT void connectedport()
{
    const ENetAddress *address = connectedpeer();
    intret(address ? address->port : -1);
};

void abortconnect()
{
    if (!connpeer)
        return;
    game::connectfail();
    if (connpeer->state != ENET_PEER_STATE_DISCONNECTED)
        enet_peer_reset(connpeer);
    connpeer = NULL;
    if (curpeer)
        return;
    enet_host_destroy(clienthost);
    clienthost = NULL;
}

SVARP(connectname, "");
VARP(connectport, 0, 0, 0xFFFF);

SCRIPTEXPORT_AS(connect)
void connectserv(const char *servername, int serverport, const char *serverpassword)
{
    if (connpeer)
    {
        conoutf("Aborting connection attempt");
        abortconnect();
    }

    if (serverport <= 0)
        serverport = game::server::ServerPort();

    ENetAddress address;
    address.port = serverport;

    if (servername)
    {
        if (strcmp(servername, connectname))
            setsvar("connectname", servername);
        if (serverport != connectport)
            setvar("connectport", serverport);
        addserver(servername, serverport, serverpassword && serverpassword[0] ? serverpassword : NULL);
        conoutf("Attempting to connect to %s:%d", servername, serverport);
        if (!resolverwait(servername, &address))
        {
            conoutf("\f3Could not resolve server %s", servername);
            return;
        }
    }
    else
    {
        setsvar("connectname", "");
        setvar("connectport", 0);
        conoutf("Attempting to connect over LAN");
        address.host = ENET_HOST_BROADCAST;
    }

    if (!clienthost)
    {
        clienthost = enet_host_create(NULL, 2, game::server::NumChannels(), rate * 1024, rate * 1024);
        if (!clienthost)
        {
            conoutf("\f3Could not connect to server");
            return;
        }
        clienthost->duplicatePeers = 0;
    }

    connpeer = enet_host_connect(clienthost, &address, game::server::NumChannels(), 0);
    enet_host_flush(clienthost);
    connmillis = shared::network::ftsClient.totalMilliseconds;
    connattempts = 0;

    game::connectattempt(servername ? servername : "", serverpassword ? serverpassword : "", address);
}

SCRIPTEXPORT void reconnect(const char *serverpassword)
{
    if (!connectname[0] || connectport <= 0)
    {
        conoutf(CON_ERROR, "No previous connection");
        return;
    }

    connectserv(connectname, connectport, serverpassword);
}

void Disconnect(bool async, bool cleanup)
{
    if (curpeer)
    {
        if (!discmillis)
        {
            enet_peer_disconnect(curpeer, engine::server::DISC_NONE);
            enet_host_flush(clienthost);
            discmillis = shared::network::ftsClient.totalMilliseconds;
        }
        if (curpeer->state != ENET_PEER_STATE_DISCONNECTED)
        {
            if (async)
                return;
            enet_peer_reset(curpeer);
        }
        curpeer = NULL;
        discmillis = 0;
        conoutf("Disconnected");
        game::gamedisconnect(cleanup);
        mainmenu = 1;
    }
    if (!connpeer && clienthost)
    {
        enet_host_destroy(clienthost);
        clienthost = NULL;
    }
}

void trydisconnect(bool local)
{
    if (connpeer)
    {
        conoutf("Aborting connection attempt");
        abortconnect();
    }
    else if (curpeer)
    {
        conoutf("Attempting to disconnect...");
        engine::server::Disconnect(!discmillis);
    }
    else if (local && engine::server::HasLocalClients())
        engine::client::LocalDisconnect();
    else
        conoutf("Not connected");
}

SCRIPTEXPORT void lanconnect(int *port, char *pw)
{
    connectserv(NULL, *port, pw);
}

SCRIPTEXPORT_AS(disconnect)
void disconnect_scriptimpl(int *local)
{
    trydisconnect(*local != 0);
}

SCRIPTEXPORT_AS(localconnect)
void localconnect_scriptimpl() //!!!!
{
    if (!engine::server::isconnected())
    {
        engine::client::LocalConnect();
    }
}

SCRIPTEXPORT_AS(localdisconnect)
void localdisconnect_scriptimpl()
{
    if (engine::server::HasLocalClients())
    {
        engine::client::LocalDisconnect();
    }
}

void sendclientpacket(ENetPacket *packet, int chan)
{
    if (curpeer)
        enet_peer_send(curpeer, chan, packet);
    else
        engine::client::LocalClientToServer(chan, packet);
}

void flushclient()
{
    if (clienthost)
        enet_host_flush(clienthost);
}

void neterr(const char *s, bool disc)
{
    conoutf(CON_ERROR, "\f3Illegal network message (%s)", s);
    if (disc)
        engine::server::Disconnect();
}

void LocalServerToClient(int chan, ENetPacket *packet) // processes any updates from the server
{
    packetbuf p(packet);
    game::parsepacketclient(chan, p);
}

void clientkeepalive()
{
    if (clienthost)
        enet_host_service(clienthost, NULL, 0);
}

void gets2c() // get updates from the server
{
    ENetEvent event;
    if (!clienthost)
        return;
    if (connpeer && shared::network::ftsClient.totalMilliseconds / 3000 > connmillis / 3000)
    {
        conoutf("Attempting to connect...");
        connmillis = shared::network::ftsClient.totalMilliseconds;
        ++connattempts;
        if (connattempts > 3)
        {
            conoutf("\f3Could not connect to server");
            abortconnect();
            return;
        }
    }
    while (clienthost && enet_host_service(clienthost, &event, 0) > 0)
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            Disconnect(false, false);
            game::server::LocalDisconnect(false);
            curpeer = connpeer;
            connpeer = NULL;
            conoutf("Connected to server");
            throttle();
            if (rate)
                setrate(rate);
            game::gameconnect(true);
            break;

        case ENET_EVENT_TYPE_RECEIVE:
            if (discmillis)
                conoutf("Attempting to disconnect...");
            else
                LocalServerToClient(event.channelID, event.packet);
            enet_packet_destroy(event.packet);
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            if (event.data >= static_cast<enet_uint32>(shared::network::protocol::DisconnectReason::NumberOfReasons))
                event.data = static_cast<enet_uint32>(shared::network::protocol::DisconnectReason::Default);

            if (event.peer == connpeer)
            {
                conoutf("\f3Could not connect to server");
                abortconnect();
            }
            else
            {
                if (!discmillis || event.data)
                {
                    const char *msg = engine::server::DisconnectReason(static_cast<shared::network::protocol::DisconnectReason>(event.data));
                    if (msg)
                    {
                        conoutf("\f3Server network error, disconnecting (%s) ...", msg);
                    }
                    else
                    {
                        conoutf("\f3Server network error, disconnecting...");
                    }
                }
                engine::server::Disconnect();
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
