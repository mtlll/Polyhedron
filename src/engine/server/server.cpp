// server.cpp: little more than enhanced multicaster
// runs dedicated or as client coroutine

#include "engine.h"
#include "engine/server/server.h"
#include "engine/client/client.h"

#include "scriptexport.h"
#include "log.h"

#include "game/game.h"
#include "game/client/client.h"
#include "game/server/server.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/protocol.h"
#include "shared/networking/cl_frametimestate.h"
#include "shared/networking/sv_frametimestate.h"

#ifdef STANDALONE
void fatal(const char *fmt, ...)
{
   void cleanupserver();
   cleanupserver();
   defvformatcubestr(msg,fmt,fmt);
   if(logfile) logoutf("%s", msg);
#ifdef WIN32
   MessageBox(NULL, msg, "SchizoMania fatal error", MB_OK|MB_SYSTEMMODAL);
#else
   fprintf(stderr, "server error: %s\n", msg);
#endif
   closelogfile();
   exit(EXIT_FAILURE);
}

void conoutfv(int type, const char *fmt, va_list args)
{
   logoutfv(fmt, args);
}

void conoutf(const char *fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   conoutfv(CON_INFO, fmt, args);
   va_end(args);
}

void conoutf(int type, const char *fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   conoutfv(type, fmt, args);
   va_end(args);
}
#endif

#define DEFAULTCLIENTS 8

enum { ST_EMPTY, ST_LOCAL, ST_TCPIP };

struct PeerClient {                 // OLD Commentary: "// server side version of "dynent" type"
    int type;
    int peerClientNumber;
    ENetPeer *peer;
    cubestr hostname;
    void *info;
};

//
// The engine side of things is obviously storing a list of all the clients, only accessable through this file.
//
namespace {
    vector<PeerClient *> peerClients;
}

namespace engine {
    namespace server {
        ENetHost *serverhost = NULL;
        int laststatus = 0;
        ENetSocket lansock = ENET_SOCKET_NULL;

        int localclients = 0, nonlocalclients = 0;

        bool hasnonlocalclients() { return nonlocalclients!=0; }
        bool haslocalclients() { return localclients!=0; }

        PeerClient &AddClient(int type)
        {
            PeerClient *c = NULL;
            loopv(peerClients) if(peerClients[i]->type==ST_EMPTY)
            {
                c = peerClients[i];
                break;
            }
            if(!c)
            {
                c = new PeerClient;
                c->peerClientNumber = peerClients.length();
                peerClients.add(c);
            }
            c->info = game::server::NewClientInfo();
            c->type = type;
            switch(type)
            {
                case ST_TCPIP: nonlocalclients++; break;
                case ST_LOCAL: localclients++; break;
            }
            return *c;
        }

        void DelClient(PeerClient *c)
        {
            if(!c) return;
            switch(c->type)
            {
                case ST_TCPIP: nonlocalclients--; if(c->peer) c->peer->data = NULL; break;
                case ST_LOCAL: localclients--; break;
                case ST_EMPTY: return;
            }
            c->type = ST_EMPTY;
            c->peer = NULL;
            if(c->info)
            {
                game::server::DeleteClientInfo(c->info);
                c->info = NULL;
            }
        }

        void CleanupServer()
        {
            if(serverhost) enet_host_destroy(serverhost);
            serverhost = NULL;

            if(lansock != ENET_SOCKET_NULL) enet_socket_destroy(lansock);
            lansock = ENET_SOCKET_NULL;
        }

        VARF(maxclients, 0, DEFAULTCLIENTS, MAXCLIENTS, { if(!maxclients) maxclients = DEFAULTCLIENTS; });
        VARF(maxdupclients, 0, 0, MAXCLIENTS, { if(serverhost) serverhost->duplicatePeers = maxdupclients ? maxdupclients : MAXCLIENTS; });

        void process(ENetPacket *packet, int sender, int chan);
        //void disconnect_client(int n, int reason);

        int GetServerMTU() { return serverhost ? serverhost->mtu : -1; }
        void *GetClientInfo(int i) { return !peerClients.inrange(i) || peerClients[i]->type==ST_EMPTY ? NULL : peerClients[i]->info; }
        ENetPeer *GetClientPeer(int i) { return peerClients.inrange(i) && peerClients[i]->type==ST_TCPIP ? peerClients[i]->peer : NULL; }
        int getnumclients()        { return peerClients.length(); }
        uint getclientip(int n)    { return peerClients.inrange(n) && peerClients[n]->type==ST_TCPIP ? peerClients[n]->peer->address.host : 0; }

        void SendPacket(int n, int chan, ENetPacket *packet, int exclude)
        {
            if(n<0)
            {
                game::server::RecordPacket(chan, packet->data, packet->dataLength);
                loopv(peerClients) if(i!=exclude && game::server::AllowBroadcast(i)) {
                    SendPacket(i, chan, packet);
                }
                return;
            }
            switch(peerClients[n]->type)
            {
                case ST_TCPIP:
                {
                    enet_peer_send(peerClients[n]->peer, chan, packet);
                    break;
                }

        #ifndef STANDALONE
                case ST_LOCAL:
                    engine::client::LocalServerToClient(chan, packet);
                break;
        #endif
            }
        }

        ENetPacket *Sendf(int cn, int chan, const char *format, ...)
        {
            int exclude = -1;
            bool reliable = false;
            if(*format=='r') { reliable = true; ++format; }
            packetbuf p(MAXTRANS, reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
            va_list args;
            va_start(args, format);
            while(*format) switch(*format++)
            {
                case 'x':
                    exclude = va_arg(args, int);
                    break;

                case 'v':
                {
                    int n = va_arg(args, int);
                    int *v = va_arg(args, int *);
                    loopi(n) shared::network::PutInt(p, v[i]);
                    break;
                }

                case 'i':
                {
                    int n = isdigit(*format) ? *format++-'0' : 1;
                    loopi(n) shared::network::PutInt(p, va_arg(args, int));
                    break;
                }
                case 'f':
                {
                    int n = isdigit(*format) ? *format++-'0' : 1;
                    loopi(n) shared::network::PutFloat(p, (float)va_arg(args, double));
                    break;
                }
                case 's': shared::network::SendCubeStr(va_arg(args, const char *), p); break;
                case 'm':
                {
                    int n = va_arg(args, int);
                    p.put(va_arg(args, uchar *), n);
                    break;
                }
            }
            va_end(args);
            ENetPacket *packet = p.finalize();
            SendPacket(cn, chan, packet, exclude);
            return packet->referenceCount > 0 ? packet : NULL;
        }

        ENetPacket *SendFile(int cn, int chan, stream *file, const char *format, ...)
        {
            if(cn < 0)
            {
        #ifdef STANDALONE
                return NULL;
        #endif
            }
            else if(!peerClients.inrange(cn)) return NULL;

            int len = (int)min(file->size(), stream::offset(INT_MAX));
            if(len <= 0 || len > 16<<20) return NULL;

            packetbuf p(MAXTRANS+len, ENET_PACKET_FLAG_RELIABLE);
            va_list args;
            va_start(args, format);
            while(*format) switch(*format++)
            {
                case 'i':
                {
                    int n = isdigit(*format) ? *format++-'0' : 1;
                    loopi(n) shared::network::PutInt(p, va_arg(args, int));
                    break;
                }
                case 's': shared::network::SendCubeStr(va_arg(args, const char *), p); break;
                case 'l': shared::network::PutInt(p, len); break;
            }
            va_end(args);

            file->seek(0, SEEK_SET);
            file->read(p.subbuf(len).buf, len);

            ENetPacket *packet = p.finalize();
            if(cn >= 0) 
                SendPacket(cn, chan, packet, -1);
        #ifndef STANDALONE
                else engine::client::SendClientPacket(packet, chan);
        #endif
            return packet->referenceCount > 0 ? packet : NULL;
        }

        const char *disconnectreason(int reason)
        {
            if (shared::network::protocol::disconnectedToStringMapper.find(static_cast<shared::network::protocol::DisconnectReason>(reason)) != shared::network::protocol::disconnectedToStringMapper.end()) {
                return shared::network::protocol::disconnectedToStringMapper[static_cast<shared::network::protocol::DisconnectReason>(reason)].c_str();
            } else {
                return "";
            }
            
        }

        void Disconnect_Client(int n, shared::network::protocol::DisconnectReason reason)
        {
            if(!peerClients.inrange(n) || peerClients[n]->type!=ST_TCPIP) return;
            enet_peer_disconnect(peerClients[n]->peer, static_cast<enet_uint32>(reason));
            game::server::ClientDisconnect(n);
            DelClient(peerClients[n]);
            const char *msg = DisconnectReason(reason);
            cubestr s;
            if(msg) formatcubestr(s, "Client (%s) disconnected because: %s", peerClients[n]->hostname, msg);
            else formatcubestr(s, "Client (%s) disconnected.", peerClients[n]->hostname);
            logoutf("%s", s);
            game::server::SendServerMessage(s);
        }

        void KickNonLocalClients(int reason)
        {
            loopv(peerClients) if(peerClients[i]->type==ST_TCPIP) Disconnect_Client(i, reason);
        }

        void Process(ENetPacket *packet, int sender, int chan)   // sender may be -1
        {
            packetbuf p(packet);
            game::server::ParsePacket(sender, chan, p);
            if(p.overread()) { Disconnect_Client(sender, DISC_EOP); return; }
        }

        void LocalClientToServer(int chan, ENetPacket *packet)
        {
            PeerClient *c = NULL;
            loopv(peerClients) if(peerClients[i]->type==ST_LOCAL) { c = peerClients[i]; break; }
            if(c) process(packet, c->peerClientNumber, chan);
        }

        #ifdef STANDALONE
            bool resolverwait(const char *name, ENetAddress *address)
            {
                return enet_address_set_host(address, name) >= 0;
            }

            int connectwithtimeout(ENetSocket sock, const char *hostname, const ENetAddress &remoteaddress)
            {
                return enet_socket_connect(sock, &remoteaddress);
            }
        #endif

        ENetSocket mastersock = ENET_SOCKET_NULL;
        ENetAddress masteraddress = { ENET_HOST_ANY, ENET_PORT_ANY }, serveraddress = { ENET_HOST_ANY, ENET_PORT_ANY };
        int lastupdatemaster = 0, lastconnectmaster = 0, masterconnecting = 0, masterconnected = 0;
        vector<char> masterout, masterin;
        int masteroutpos = 0, masterinpos = 0;
        VARN(updatemaster, allowupdatemaster, 0, 1, 1);

        void DisconnectMaster()
        {
            if(mastersock != ENET_SOCKET_NULL)
            {
                game::server::MasterDisconnected();
                enet_socket_destroy(mastersock);
                mastersock = ENET_SOCKET_NULL;
            }

            masterout.setsize(0);
            masterin.setsize(0);
            masteroutpos = masterinpos = 0;

            masteraddress.host = ENET_HOST_ANY;
            masteraddress.port = ENET_PORT_ANY;

            lastupdatemaster = masterconnecting = masterconnected = 0;
        }

        SVARF(mastername, game::server::DefaultMaster(), engine::server::DisconnectMaster());
        VARF(masterport, 1, game::server::MasterPort(), 0xFFFF, engine::server::DisconnectMaster());

        ENetSocket connectmaster(bool wait)
        {
            if(!mastername[0]) return ENET_SOCKET_NULL;
            if(masteraddress.host == ENET_HOST_ANY)
            {
                if(IsDedicatedServer()) logoutf("Looking up %s...", mastername);
                masteraddress.port = masterport;
                if(!resolverwait(mastername, &masteraddress)) return ENET_SOCKET_NULL;
            }
            ENetSocket sock = enet_socket_create(ENET_SOCKET_TYPE_STREAM);
            if(sock == ENET_SOCKET_NULL)
            {
                if(IsDedicatedServer()) logoutf("could not open master server socket");
                return ENET_SOCKET_NULL;
            }
            if(wait || serveraddress.host == ENET_HOST_ANY || !enet_socket_bind(sock, &serveraddress))
            {
                enet_socket_set_option(sock, ENET_SOCKOPT_NONBLOCK, 1);
                if(wait)
                {
                    if(!connectwithtimeout(sock, mastername, masteraddress)) return sock;
                }
                else if(!enet_socket_connect(sock, &masteraddress)) return sock;
            }
            enet_socket_destroy(sock);
            if(IsDedicatedServer()) logoutf("could not connect to master server");
            return ENET_SOCKET_NULL;
        }

        bool RequestMaster(const char *req)
        {
            if(mastersock == ENET_SOCKET_NULL)
            {
                mastersock = connectmaster(false);
                if(mastersock == ENET_SOCKET_NULL) return false;
                lastconnectmaster = masterconnecting = shared::network::ftsClient.totalMilliseconds ? shared::network::ftsClient.totalMilliseconds : 1;
            }

            if(masterout.length() >= 4096) return false;

            masterout.put(req, strlen(req));
            return true;
        }

        bool RequestMasterf(const char *fmt, ...)
        {
            defvformatcubestr(req, fmt, fmt);
            return RequestMaster(req);
        }

        void ProcessMasterInput()
        {
            if(masterinpos >= masterin.length()) return;

            char *input = &masterin[masterinpos], *end = (char *)memchr(input, '\n', masterin.length() - masterinpos);
            while(end)
            {
                *end = '\0';

                const char *args = input;
                while(args < end && !iscubespace(*args)) args++;
                int cmdlen = args - input;
                while(args < end && iscubespace(*args)) args++;

                if(matchcubestr(input, cmdlen, "failreg"))
                    conoutf(CON_ERROR, "Master server registration failed: %s", args);
                else if(matchcubestr(input, cmdlen, "succreg"))
                    conoutf("Master server registration succeeded");
                else game::server::ProcessMasterInput(input, cmdlen, args); // WatIsDeze : Mike -> This one is for the game, ambigioutious code Eihrul!!!

                end++;
                masterinpos = end - masterin.getbuf();
                input = end;
                end = (char *)memchr(input, '\n', masterin.length() - masterinpos);
            }

            if(masterinpos >= masterin.length())
            {
                masterin.setsize(0);
                masterinpos = 0;
            }
        }

        void FlushMasterOutput()
        {
            if(masterconnecting && shared::network::ftsClient.totalMilliseconds - masterconnecting >= 60000)
            {
                logoutf("Could not connect to master server");
                DisconnectMaster();
            }
            if(masterout.empty() || !masterconnected) return;

            ENetBuffer buf;
            buf.data = &masterout[masteroutpos];
            buf.dataLength = masterout.length() - masteroutpos;
            int sent = enet_socket_send(mastersock, NULL, &buf, 1);
            if(sent >= 0)
            {
                masteroutpos += sent;
                if(masteroutpos >= masterout.length())
                {
                    masterout.setsize(0);
                    masteroutpos = 0;
                }
            }
            else DisconnectMaster();
        }

        void FlushMasterInput()
        {
            if(masterin.length() >= masterin.capacity())
                masterin.reserve(4096);

            ENetBuffer buf;
            buf.data = masterin.getbuf() + masterin.length();
            buf.dataLength = masterin.capacity() - masterin.length();
            int recv = enet_socket_receive(mastersock, NULL, &buf, 1);
            if(recv > 0)
            {
                masterin.advance(recv);
                ProcessMasterInput();
            }
            else DisconnectMaster();
        }

        static ENetAddress serverinfoaddress;

        void sendserverinforeply(ucharbuf &p)
        {
            ENetBuffer buf;
            buf.data = p.buf;
            buf.dataLength = p.length();
            enet_socket_send(serverhost->socket, &serverinfoaddress, &buf, 1);
        }

        #define MAXPINGDATA 32

        void CheckServerSockets()        // reply all server info requests
        {
            static ENetSocketSet readset, writeset;
            ENET_SOCKETSET_EMPTY(readset);
            ENET_SOCKETSET_EMPTY(writeset);
            ENetSocket maxsock = ENET_SOCKET_NULL;
            if(mastersock != ENET_SOCKET_NULL)
            {
                maxsock = maxsock == ENET_SOCKET_NULL ? mastersock : max(maxsock, mastersock);
                ENET_SOCKETSET_ADD(readset, mastersock);
                if(!masterconnected) ENET_SOCKETSET_ADD(writeset, mastersock);
            }
            if(lansock != ENET_SOCKET_NULL)
            {
                maxsock = maxsock == ENET_SOCKET_NULL ? lansock : max(maxsock, lansock);
                ENET_SOCKETSET_ADD(readset, lansock);
            }
            if(maxsock == ENET_SOCKET_NULL || enet_socketset_select(maxsock, &readset, &writeset, 0) <= 0) return;

            if(lansock != ENET_SOCKET_NULL && ENET_SOCKETSET_CHECK(readset, lansock))
            {
                ENetBuffer buf;
                uchar data[MAXTRANS];
                buf.data = data;
                buf.dataLength = sizeof(data);
                int len = enet_socket_receive(lansock, &serverinfoaddress, &buf, 1);
                if(len < 2 || data[0] != 0xFF || data[1] != 0xFF || len-2 > MAXPINGDATA) return;
                ucharbuf req(data+2, len-2), p(data+2, sizeof(data)-2);
                p.len += len-2;
                game::server::ServerInfoReply(req, p);
            }

            if(mastersock != ENET_SOCKET_NULL)
            {
                if(!masterconnected)
                {
                    if(ENET_SOCKETSET_CHECK(readset, mastersock) || ENET_SOCKETSET_CHECK(writeset, mastersock))
                    {
                        int error = 0;
                        if(enet_socket_get_option(mastersock, ENET_SOCKOPT_ERROR, &error) < 0 || error)
                        {
                            logoutf("Could not connect to master server");
                            DisconnectMaster();
                        }
                        else
                        {
                            masterconnecting = 0;
                            masterconnected = shared::network::ftsClient.totalMilliseconds ? shared::network::ftsClient.totalMilliseconds : 1;
                            game::server::MasterConnected();
                        }
                    }
                }
                if(mastersock != ENET_SOCKET_NULL && ENET_SOCKETSET_CHECK(readset, mastersock)) FlushMasterInput();
            }
        }

        static int serverinfointercept(ENetHost *host, ENetEvent *event)
        {
            if(host->receivedDataLength < 2 || host->receivedData[0] != 0xFF || host->receivedData[1] != 0xFF || host->receivedDataLength-2 > MAXPINGDATA) return 0;
            serverinfoaddress = host->receivedAddress;
            ucharbuf req(host->receivedData+2, host->receivedDataLength-2), p(host->receivedData+2, sizeof(host->packetData[0])-2);
            p.len += host->receivedDataLength-2;
            game::server::ServerInfoReply(req, p);
            return 1;
        }

        VAR(serveruprate, 0, 0, INT_MAX);
        SVAR(serverip, "");
        VARF(serverport, 0, game::server::ServerPort(), 0xFFFF, { if(!serverport) serverport = game::server::ServerPort(); });

        #ifdef STANDALONE
            shared::network::FrameStateTime fstClient; // WatIsDeze: Mike: TODO: Should this not be fstServer? Hehehe
            int curtime = 0, lastmillis = 0, elapsedtime = 0, totalmillis = 0;
        #endif

        void UpdateMasterServer()
        {
            if(!masterconnected && lastconnectmaster && shared::network::ftsClient.totalMilliseconds-lastconnectmaster <= 5*60*1000) return;
            if(mastername[0] && allowupdatemaster) RequestMasterf("regserv %d\n", serverport);
            lastupdatemaster = shared::network::ftsClient.totalMilliseconds ? shared::network::ftsClient.totalMilliseconds : 1;
        }

        uint totalsecs = 0;

        void updatetime()
        {
            static int lastsec = 0;
            if(shared::network::ftsClient.totalMilliseconds - lastsec >= 1000)
            {
                int cursecs = (shared::network::ftsClient.totalMilliseconds - lastsec) / 1000;
                totalsecs += cursecs;
                lastsec += cursecs * 1000;
            }
        }

        void ServerSlice(bool dedicated, uint timeout)   // main server update, called from main loop in sp, or from below in dedicated server
        {
            if(!serverhost)
            {
                game::server::ServerUpdate();
                game::server::SendPackets();
                return;
            }

            // below is network only

            if(dedicated)
            {
                int millis = (int)enet_time_get();
                shared::network::ftsClient.elapsedTime = millis - shared::network::ftsClient.totalMilliseconds;
                static int timeerr = 0;
                int scaledtime = game::server::ScaleTime(shared::network::ftsClient.elapsedTime) + timeerr;
                shared::network::ftsClient.currentTime = scaledtime/100;
                timeerr = scaledtime%100;
                if(game::server::IsPaused()) shared::network::ftsClient.currentTime = 0;
                shared::network::ftsClient.lastMilliseconds += shared::network::ftsClient.currentTime;
                shared::network::ftsClient.totalMilliseconds = millis;
                updatetime();
            }
            game::server::ServerUpdate();

            FlushMasterOutput();
            CheckServerSockets();

            if(!lastupdatemaster || shared::network::ftsClient.totalMilliseconds-lastupdatemaster>60*60*1000)       // send alive signal to masterserver every hour of uptime
                UpdateMasterServer();

            if(shared::network::ftsClient.totalMilliseconds-laststatus>60*1000)   // display bandwidth stats, useful for server ops
            {
                laststatus = shared::network::ftsClient.totalMilliseconds;
                if(nonlocalclients || serverhost->totalSentData || serverhost->totalReceivedData) logoutf("status: %d remote clients, %.1f send, %.1f rec (K/sec)", nonlocalclients, serverhost->totalSentData/60.0f/1024, serverhost->totalReceivedData/60.0f/1024);
                serverhost->totalSentData = serverhost->totalReceivedData = 0;
            }

            ENetEvent event;
            bool serviced = false;
            while(!serviced)
            {
                if(enet_host_check_events(serverhost, &event) <= 0)
                {
                    if(enet_host_service(serverhost, &event, timeout) <= 0) break;
                    serviced = true;
                }
                switch(event.type)
                {
                    case ENET_EVENT_TYPE_CONNECT:
                    {
                        PeerClient &c = AddClient(ST_TCPIP);
                        c.peer = event.peer;
                        c.peer->data = &c;
                        cubestr hn;
                        copycubestr(c.hostname, (enet_address_get_host_ip(&c.peer->address, hn, sizeof(hn))==0) ? hn : "unknown");
                        logoutf("Client connected (%s)", c.hostname);
                        shared::network::protocol::DisconnectReason reason = game::server::ClientConnect(c.peerClientNumber, c.peer->address.host);
                        if(reason == shared::network::protocol::DisconnectReason::Default) {
                            Disconnect_Client(c.peerClientNumber, reason);
                        }
                        break;
                    }
                    case ENET_EVENT_TYPE_RECEIVE:
                    {
                        PeerClient *c = (PeerClient *)event.peer->data;
                        if(c) process(event.packet, c->peerClientNumber, event.channelID);
                        if(event.packet->referenceCount==0) enet_packet_destroy(event.packet);
                        break;
                    }
                    case ENET_EVENT_TYPE_DISCONNECT:
                    {
                        PeerClient *c = (PeerClient *)event.peer->data;
                        if(!c) break;
                        logoutf("Disconnected client ^f4 (%s)", c->hostname);
                        game::server::ClientDisconnect(c->peerClientNumber);
                        DelClient(c);
                        break;
                    }
                    default:
                        break;
                }
            }
            if(game::server::SendPackets()) enet_host_flush(serverhost);
        }

        void flushserver(bool force)
        {
            if(game::server::SendPackets(force) && serverhost) enet_host_flush(serverhost);
        }
    };
       #ifndef STANDALONE
            void LocalDisconnect(bool cleanup)
            {
                bool disconnected = false;
                loopv(peerClients) if(peerClients[i]->type==ST_LOCAL) {
                    engine::LocalDisconnect(i);
                    engine::server::DelClient(peerClients[i]);
                    disconnected = true;
                }
                if(!disconnected) return;
                game::gamedisconnect(cleanup);
                mainmenu = 1;
            }

            void LocalConnect()
            {
                PeerClient &c = engine::server::AddClient(ST_LOCAL);
                copycubestr(c.hostname, "local");
                game::gameconnect(false);
                game::server::LocalConnect(c.peerClientNumber);
            }
        #endif

#ifdef WIN32
#include "shellapi.h"

#define IDI_ICON1 1

static cubestr apptip = "";
static HINSTANCE appinstance = NULL;
static ATOM wndclass = 0;
static HWND appwindow = NULL, conwindow = NULL;
static HICON appicon = NULL;
static HMENU appmenu = NULL;
static HANDLE outhandle = NULL;
static const int MAXLOGLINES = 200;
struct logline { int len; char buf[LOGSTRLEN]; };
static queue<logline, MAXLOGLINES> loglines;

static void cleanupsystemtray()
{
    NOTIFYICONDATA nid;
    memset(&nid, 0, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.hWnd = appwindow;
    nid.uID = IDI_ICON1;
    Shell_NotifyIcon(NIM_DELETE, &nid);
}

static bool setupsystemtray(UINT uCallbackMessage)
{
    NOTIFYICONDATA nid;
    memset(&nid, 0, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.hWnd = appwindow;
    nid.uID = IDI_ICON1;
    nid.uCallbackMessage = uCallbackMessage;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.hIcon = appicon;
    strcpy(nid.szTip, apptip);
    if(Shell_NotifyIcon(NIM_ADD, &nid) != TRUE)
        return false;
    atexit(cleanupsystemtray);
    return true;
}

#if 0
static bool modifysystemtray()
{
    NOTIFYICONDATA nid;
    memset(&nid, 0, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.hWnd = appwindow;
    nid.uID = IDI_ICON1;
    nid.uFlags = NIF_TIP;
    strcpy(nid.szTip, apptip);
    return Shell_NotifyIcon(NIM_MODIFY, &nid) == TRUE;
}
#endif

static void cleanupwindow()
{
    if(!appinstance) return;
    if(appmenu)
    {
        DestroyMenu(appmenu);
        appmenu = NULL;
    }
    if(wndclass)
    {
        UnregisterClass(MAKEINTATOM(wndclass), appinstance);
        wndclass = 0;
    }
}

static BOOL WINAPI consolehandler(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_CLOSE_EVENT:
            exit(EXIT_SUCCESS);
            return TRUE;
    }
    return FALSE;
}

static void writeline(logline &line)
{
    static uchar ubuf[512];
    size_t len = strlen(line.buf), carry = 0;
    while(carry < len)
    {
        size_t numu = encodeutf8(ubuf, sizeof(ubuf), &((uchar *)line.buf)[carry], len - carry, &carry);
        DWORD written = 0;
        WriteConsole(outhandle, ubuf, numu, &written, NULL);
    }
}

static void setupconsole()
{
    if(conwindow) return;
    if(!AllocConsole()) return;
    SetConsoleCtrlHandler(consolehandler, TRUE);
    conwindow = GetConsoleWindow();
    SetConsoleTitle(apptip);
    //SendMessage(conwindow, WM_SETICON, ICON_SMALL, (LPARAM)appicon);
    SendMessage(conwindow, WM_SETICON, ICON_BIG, (LPARAM)appicon);
    outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(outhandle, &coninfo);
    coninfo.dwSize.Y = MAXLOGLINES;
    SetConsoleScreenBufferSize(outhandle, coninfo.dwSize);
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    loopv(loglines) writeline(loglines[i]);
}

enum
{
    MENU_OPENCONSOLE = 0,
    MENU_SHOWCONSOLE,
    MENU_HIDECONSOLE,
    MENU_EXIT
};

static LRESULT CALLBACK handlemessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_APP:
            SetForegroundWindow(hWnd);
            switch(lParam)
            {
                //case WM_MOUSEMOVE:
                //	break;
                case WM_LBUTTONUP:
                case WM_RBUTTONUP:
                {
                    POINT pos;
                    GetCursorPos(&pos);
                    TrackPopupMenu(appmenu, TPM_CENTERALIGN|TPM_BOTTOMALIGN|TPM_RIGHTBUTTON, pos.x, pos.y, 0, hWnd, NULL);
                    PostMessage(hWnd, WM_NULL, 0, 0);
                    break;
                }
            }
            return 0;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case MENU_OPENCONSOLE:
                    setupconsole();
                    if(conwindow) ModifyMenu(appmenu, 0, MF_BYPOSITION|MF_STRING, MENU_HIDECONSOLE, "Hide Console");
                    break;
                case MENU_SHOWCONSOLE:
                    ShowWindow(conwindow, SW_SHOWNORMAL);
                    ModifyMenu(appmenu, 0, MF_BYPOSITION|MF_STRING, MENU_HIDECONSOLE, "Hide Console");
                    break;
                case MENU_HIDECONSOLE:
                    ShowWindow(conwindow, SW_HIDE);
                    ModifyMenu(appmenu, 0, MF_BYPOSITION|MF_STRING, MENU_SHOWCONSOLE, "Show Console");
                    break;
                case MENU_EXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
            }
            return 0;
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

static void setupwindow(const char *title)
{
    copycubestr(apptip, title);
    //appinstance = GetModuleHandle(NULL);
    if(!appinstance) fatal("failed getting application instance");
    appicon = LoadIcon(appinstance, MAKEINTRESOURCE(IDI_ICON1));//(HICON)LoadImage(appinstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
    if(!appicon) fatal("failed loading icon");

    appmenu = CreatePopupMenu();
    if(!appmenu) fatal("failed creating popup menu");
    AppendMenu(appmenu, MF_STRING, MENU_OPENCONSOLE, "Open Console");
    AppendMenu(appmenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(appmenu, MF_STRING, MENU_EXIT, "Exit");
    //SetMenuDefaultItem(appmenu, 0, FALSE);

    WNDCLASS wc;
    memset(&wc, 0, sizeof(wc));
    wc.hCursor = NULL; //LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = appicon;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = title;
    wc.style = 0;
    wc.hInstance = appinstance;
    wc.lpfnWndProc = handlemessages;
    wc.cbWndExtra = 0;
    wc.cbClsExtra = 0;
    wndclass = RegisterClass(&wc);
    if(!wndclass) fatal("failed registering window class");

    appwindow = CreateWindow(MAKEINTATOM(wndclass), title, 0, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, HWND_MESSAGE, NULL, appinstance, NULL);
    if(!appwindow) fatal("failed creating window");

    atexit(cleanupwindow);

    if(!setupsystemtray(WM_APP)) fatal("failed adding to system tray");
}

static char *parsecommandline(const char *src, vector<char *> &args)
{
    char *buf = new char[strlen(src) + 1], *dst = buf;
    for(;;)
    {
        while(isspace(*src)) src++;
        if(!*src) break;
        args.add(dst);
        for(bool quoted = false; *src && (quoted || !isspace(*src)); src++)
        {
            if(*src != '"') *dst++ = *src;
            else if(dst > buf && src[-1] == '\\') dst[-1] = '"';
            else quoted = !quoted;
        }
        *dst++ = '\0';
    }
    args.add(NULL);
    return buf;
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
{
    vector<char *> args;
    char *buf = parsecommandline(GetCommandLine(), args);
    appinstance = hInst;
#ifdef STANDALONE
    int standalonemain(int argc, char **argv);
    int status = standalonemain(args.length()-1, args.getbuf());
    #define main standalonemain
#else
    SDL_SetMainReady();
    int status = SDL_main(args.length()-1, args.getbuf());
#endif
    delete[] buf;
    exit(status);
    return 0;
}

void logoutfv(const char *fmt, va_list args)
{
    if(appwindow)
    {
        logline &line = loglines.add();
        vformatcubestr(line.buf, fmt, args, sizeof(line.buf));
        if(logfile) writelog(logfile, line.buf);
        line.len = min(strlen(line.buf), sizeof(line.buf)-2);
        line.buf[line.len++] = '\n';
        line.buf[line.len] = '\0';
        if(outhandle) writeline(line);
    }
    else if(logfile) writelogv(logfile, fmt, args);
}

#else

// void logoutfv(const char *fmt, va_list args)
// {
//     FILE *f = getlogfile();
//     if(f) writelogv(f, fmt, args);
// }

#endif

static bool dedicatedserver = false;

bool IsDedicatedServer() { return dedicatedserver; }

void RunDedicatedServer()
{
    dedicatedserver = true;
    logoutf("Dedicated server started, waiting for clients...");
#ifdef WIN32
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    for(;;)
    {
        MSG msg;
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT) exit(EXIT_SUCCESS);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        serverslice(true, 5);
    }
#else
    for(;;) engine::server::ServerSlice(true, 5);
#endif
    dedicatedserver = false;
}

bool servererror(bool dedicated, const char *desc)
{
#ifndef STANDALONE
    if(!dedicated)
    {
        conoutf(CON_ERROR, "%s", desc);
        engine::server::CleanupServer();
    }
    else
#endif
        fatal("%s", desc);
    return false;
}

bool SetupListenServer(bool dedicated)
{
    ENetAddress address = { ENET_HOST_ANY, enet_uint16(engine::server::serverport <= 0 ? game::server::ServerPort() : engine::server::serverport) };
    if(*engine::server::serverip)
    {
        if(enet_address_set_host(&address, engine::server::serverip)<0) conoutf(CON_WARN, "WARNING: Server IP Address not resolved");
        else server::serveraddress.host = address.host;
    }
    engine::server::serverhost = enet_host_create(&address, min(engine::server::maxclients + game::server::ReserveClients(), MAXCLIENTS), game::server::NumberOfChannels(), 0, engine::server::serveruprate);
    if(!engine::server::serverhost) return servererror(dedicated, "Could not create server host");
    engine::server::serverhost->duplicatePeers = engine::server::maxdupclients ? engine::server::maxdupclients : MAXCLIENTS;
    engine::server::serverhost->intercept = engine::server::serverinfointercept;
    address.port = game::server::LanInfoPort();
    engine::server::lansock = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM);
    if(engine::server::lansock != ENET_SOCKET_NULL && (enet_socket_set_option(engine::server::lansock, ENET_SOCKOPT_REUSEADDR, 1) < 0 || enet_socket_bind(engine::server::lansock, &address) < 0))
    {
        enet_socket_destroy(engine::server::lansock);
        engine::server::lansock = ENET_SOCKET_NULL;
    }
    if(engine::server::lansock == ENET_SOCKET_NULL) conoutf(CON_WARN, "WARNING: could not create LAN server info socket");
    else enet_socket_set_option(engine::server::lansock, ENET_SOCKOPT_NONBLOCK, 1);
    return true;
}

void InitServer(bool listen, bool dedicated)
{
    if(dedicated)
    {
#ifdef WIN32
        setupwindow("SchizoMania server");
#endif
    }

    execfile("config/server-init.cfg", false);

    if(listen) SetupListenServer(dedicated);

    game::server::ServerInit();

    if(listen)
    {
        dedicatedserver = dedicated;
        engine::server::UpdateMasterServer();
        if(dedicated) RunDedicatedServer(); // never returns
#ifndef STANDALONE
        else conoutf("Listen server started");
#endif
    }
}

#ifndef STANDALONE
SCRIPTEXPORT_AS(startlistenserver) void StartListenServer(int *usemaster) {
    if(engine::server::serverhost) { conoutf(CON_ERROR, "Listen server is already running"); return; }

    engine::server::allowupdatemaster = *usemaster>0 ? 1 : 0;

    if(!SetupListenServer(false)) return;

    engine::server::UpdateMasterServer();

    conoutf("Listen server started for %d clients%s", engine::server::maxclients, engine::server::allowupdatemaster ? " and listed with master server" : "");
}

SCRIPTEXPORT_AS(stoplistenserver) void StopListenServer() {
    if(!engine::server::serverhost) { conoutf(CON_ERROR, "Listen server is not running"); return; }

    engine::server::KickNonLocalClients();
    enet_host_flush(engine::server::serverhost);
    engine::server::CleanupServer();

    conoutf("Listen server stopped");
}
#endif

bool ServerOption(char *opt) {
    switch(opt[1])
    {
#ifdef STANDALONE
        case 'u': logoutf("Using home directory: %s", opt); sethomedir(opt+2); return true;
        case 'k': logoutf("Adding package directory: %s", opt); addpackagedir(opt+2); return true;
        case 'g': logoutf("Setting log file: %s", opt); setlogfile(opt+2); return true;
#endif
        default: return false;
    }

    // I know right... why over here??
    vector<const char *> gameargs;
};
}; // server



#ifdef STANDALONE
int main(int argc, char **argv)
{
    setlogfile(NULL);
    if(enet_initialize()<0) fatal("Unable to initialise network module");
    atexit(enet_deinitialize);
    enet_time_set(0);
    for(int i = 1; i<argc; i++) if(argv[i][0]!='-' || !serveroption(argv[i])) gameargs.add(argv[i]);
    game::parseoptions(engine::servergameargs);
    initserver(true, true);
    return EXIT_SUCCESS;
}
#endif


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
#if 0
#include "/Users/micha/dev/ScMaMike/src/build/binding/..+engine+server.binding.cpp"
#endif
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
