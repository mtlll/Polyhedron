// server.cpp: little more than enhanced multicaster
// runs dedicated or as client coroutine

#include "engine.h"
#include "scriptexport.h"
#include "log.h"

#include "game/game.h"
#include "game/client/client.h"
#include "game/server/server.h"

#include "shared/networking/network.h"
#include "shared/networking/protocol.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/cl_sv.h"

#ifdef STANDALONE
void fatal(const char *fmt, ...)
{
   void CleanupServer();
   CleanupServer();
   defvformatcubestr(msg,fmt,fmt);
   if(logfile) logoutf("%s", msg);
#ifdef WIN32
   MessageBox(NULL, msg, "Polyhedron fatal error", MB_OK|MB_SYSTEMMODAL);
#else
   fprintf(stderr, "Server Error: %s\n", msg);
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

namespace game {
    namespace server {
        vector<game::networking::ServerClient *> clients;
    };
};

struct HostServerInfo {
    ENetHost *serverHost = NULL;
    ENetSocket lanSock = ENET_SOCKET_NULL;

    int lastStatus = 0;

    int localClients = 0;
    int nonLocalClients = 0;
} hostServerInfo;

bool HasNonLocalClients() { 
    return hostServerInfo.nonLocalClients!=0; 
}
bool HasLocalClients() { 
    return hostServerInfo.localClients!=0; 
}

game::networking::ServerClient &AddClient(game::networking::ServerState type)
{
    game::networking::ServerClient *c = NULL;
        
    loopv(game::server::clients) if(game::server::clients[i]->type ==game::networking::ServerState::Empty)
    {
        c = game::server::clients[i];
        break;
    }
    if(!c)
    {
        c = new game::networking::ServerClient;
        c->clientNumber = game::server::clients.length();
        game::server::clients.add(c);
    }
    c->info = game::server::NewClientInfo();
    c->type = type;
    switch(type)
    {
        case game::networking::ServerState::TcpIP:
            hostServerInfo.nonLocalClients++;
        break;
        case game::networking::ServerState::Local: 
            hostServerInfo.localClients++; 
        break;
        case game::networking::ServerState::Empty:
            #ifdef DEBUG
            conoutf("%s ServerState::Empty - nonLocalClients: %i - localClients: %i", nonLocalClients, localClients);
            #else 
            conoutf("%s", "Empty ServerState");
            #endif
    }
    return *c;
}

void DelClient(game::networking::ServerClient *c)
{
    if(!c) return;
    switch(c->type)
    {
        case game::networking::ServerState::TcpIP: hostServerInfo.nonLocalClients--; if(c->peer) c->peer->data = NULL; break;
        case game::networking::ServerState::Local: hostServerInfo.localClients--; break;
        case game::networking::ServerState::Empty: 
            c->type = game::networking::ServerState::Empty;
            break;
    }
    c->type = game::networking::ServerState::Empty;
    c->peer = NULL;
    if(c->info)
    {
        game::server::DeleteClientInfo(c->info);
        c->info = NULL;
    }
}

void CleanupServer()
{
    if(hostServerInfo.serverHost) enet_host_destroy(hostServerInfo.serverHost);
        hostServerInfo.serverHost = NULL;

    if(hostServerInfo.lanSock != ENET_SOCKET_NULL) enet_socket_destroy(hostServerInfo.lanSock);
        hostServerInfo.lanSock = ENET_SOCKET_NULL;
}

VARF(maxclients, 0, DEFAULTCLIENTS, MAXCLIENTS, { if(!maxclients) maxclients = DEFAULTCLIENTS; });
VARF(maxdupclients, 0, 0, MAXCLIENTS, { if(hostServerInfo.serverHost) hostServerInfo.serverHost->duplicatePeers = maxdupclients ? maxdupclients : MAXCLIENTS; });

extern void Process(ENetPacket *packet, int sender, int chan);
extern void Disconnect_Client(int n, int reason);

int GetServerMTU() { return hostServerInfo.serverHost ? hostServerInfo.serverHost->mtu : -1; }
void *GetClientInfo(int i) { return !game::server::clients.inrange(i) || game::server::clients[i]->type==game::networking::ServerState::Empty ? NULL : game::server::clients[i]->info; }
ENetPeer *GetClientPeer(int i) { return game::server::clients.inrange(i) && game::server::clients[i]->type==game::networking::ServerState::TcpIP ? game::server::clients[i]->peer : NULL; }
int GetNumClients()        { return game::server::clients.length(); }
uint GetClientIP(int n)    { return game::server::clients.inrange(n) && game::server::clients[n]->type==game::networking::ServerState::TcpIP ? game::server::clients[n]->peer->address.host : 0;}

void SendPacket(int n, int chan, ENetPacket *packet, int exclude)
{
    if(n<0)
    {
        game::server::RecordPacket(chan, packet->data, packet->dataLength);
        loopv(game::server::clients) {
            if(i!=exclude && game::server::AllowBroadcast(i)) 
                game::networking::SendPacket(i, chan, packet);

            switch(game::server::clients[n]->type)
            {
                case game::networking::ServerState::TcpIP: {
                    enet_peer_send(game::server::clients[n]->peer, chan, packet);
                    break;
                }
                case game::networking::ServerState::Empty: {
                    break;
                }
        #ifndef STANDALONE
                case game::networking::ServerState::Local: {
                    LocalServerToClient(chan, packet);
                    break;
                };
        #endif
                default:
                        break;
            };
        };
    };
}

    struct MasterConnection {
        ENetAddress masterAddress = { ENET_HOST_ANY, ENET_PORT_ANY };
        ENetAddress serverAddress = { ENET_HOST_ANY, ENET_PORT_ANY };
        ENetSocket masterSock = ENET_SOCKET_NULL;

        int masterConnecting = 0;
        int masterConnected = 0;

        int lastUpdateMaster = 0;
        int lastConnectMaster = 0;

        vector<char> masterOut;
        vector<char> masterIn;

        int masterOutPos = 0;
        int masterInPos = 0;
    };
    MasterConnection masterConnection;

    VARN(updatemaster, allowUpdateMaster, 0, 1, 1);
    namespace networking {
        ENetPacket *sendf(int cn, int chan, const char *format, ...)
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
                    loopi(n) game::networking::putint(p, v[i]);
                    break;
                }

                case 'i':
                {
                    int n = isdigit(*format) ? *format++-'0' : 1;
                    loopi(n) game::networking::putint(p, va_arg(args, int));
                    break;
                }
                case 'f':
                {
                    int n = isdigit(*format) ? *format++-'0' : 1;
                    loopi(n) game::networking::putfloat(p, (float)va_arg(args, double));
                    break;
                }
                case 's': game::networking::sendcubestr(va_arg(args, const char *), p); break;
                case 'S': game::networking::sendcubestr(va_arg(args, const char *), p); break;
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

        ENetPacket *sendfile(int cn, int chan, stream *file, const char *format, ...)
        {
            if(cn < 0)
            {
        #ifdef STANDALONE
                return NULL;
        #endif
            }
            else if(!game::server::clients.inrange(cn)) return NULL;

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
                    loopi(n) game::networking::putint(p, va_arg(args, int));
                    break;
                }
                case 's': game::networking::sendcubestr(va_arg(args, const char *), p); break;
                case 'l': game::networking::putint(p, len); break;
            }
            va_end(args);

            file->seek(0, SEEK_SET);
            file->read(p.subbuf(len).buf, len);

            ENetPacket *packet = p.finalize();
            if(cn >= 0) SendPacket(cn, chan, packet, -1);
        #ifndef STANDALONE
            else game::networking::SendClientPacket(packet, chan);
        #endif
            return packet->referenceCount > 0 ? packet : NULL;
        }

        const std::string &DisconnectReason(game::networking::protocol::DisconnectReason reason = game::networking::protocol::DisconnectReason::Default)
        {
            if (game::networking::protocol::DisConnectedToStringMapper.find(reason) != game::networking::protocol::DisConnectedToStringMapper.end())
            {
                return game::networking::protocol::DisConnectedToStringMapper.at(reason);
            }
            else
            {
                static std::string retval = ("Unknown Disconnection error");
                return retval;
            }
        
            // switch(reason)
            // {
            //     case game::networking::protocol::DisconectReason::EndOfPacket: return "end of packet";
            //     case game::networking::protocol::EndOfPacket: = "End of Packet",
            //     case game::networking::protocol::Local = "The server is in Local Mode",
            //     case game::networking::protocol::Kick = "Kicked or Banned",
            //     case game::networking::protocol::MessageError = "Message Error",         // Likely when someone sends an invalid message. (Cheats or uses an outdated client, or we ourselves introduced a bug! Bad boys!)
            //     case game::networking::protocol::IPBan = "Your IP is banned",
            //     case game::networking::protocol::Private = "This server is in Private Mode",
            //     case game::networking::protocol::MaximumClients = "This server has reached the maximum amount of clients",
            //     case game::networking::protocol::TimeOut = "Connection timed out",
            //     case game::networking::protocol::Password: return "Invalid Password";
            //     default: return "";
            // }
        }

        void Disconnect_Client(int n, game::networking::protocol::DisconnectReason reason)
        {
            if(!game::server::clients.inrange(n) || game::server::clients[n]->type!=game::networking::ServerState::TcpIP) return;
            enet_peer_disconnect(game::server::clients[n]->peer, static_cast<enet_uint32>(reason));
            game::server::ClientDisconnect(n);
            DelClient(game::server::clients[n]);
            std::string msg = game::networking::DisconnectReason(reason);
            cubestr s;
            if(!msg.empty()) formatcubestr(s, "client (%s) DisConnected because: %s", game::server::clients[n]->hostName, msg.c_str());
            else formatcubestr(s, "client (%s) DisConnected", game::server::clients[n]->hostName);
            logoutf("%s", s);
            game::server::SendServMsg(s);
        }

        void KickNonLocalclients(game::networking::protocol::DisconnectReason reason)
        {
            loopv(game::server::clients) 
                if(game::server::clients[i]->type==game::networking::ServerState::TcpIP)
                   game::networking::Disconnect_Client(i, reason);
        }

        void Process(ENetPacket *packet, int sender, int chan)   // sender may be -1
        {
            packetbuf p(packet);
            game::server::ParsePacket(sender, chan, p);
            if(p.overread()) { 
                game::networking::Disconnect_Client(sender, game::networking::protocol::DisconnectReason::EndOfPacket);
                return; 
            }
        }

        void LocalClientToServer(int chan, ENetPacket *packet)
        {
            game::networking::ServerClient *c = NULL;

            loopv(game::server::clients) {
                if(game::server::clients[i]->type==game::networking::ServerState::Local) { 
                    c = game::server::clients[i]; 
                    break;
                }
            }
            if(c) ::Process(packet, c->clientNumber, chan);
        }

        #ifdef STANDALONE
        bool ResolverWait(const char *name, ENetAddress *address)
        {
            return enet_address_set_host(address, name) >= 0;
        }

        int ConnectWithTimeout(ENetSocket sock, const char *hostName, const ENetAddress &remoteAddress)
        {
            return enet_socket_connect(sock, &remoteAddress);
        }
        #endif

    namespace networking {
        cubestr masterName;

        ENetSocket ConnectMaster(bool wait)
        {
            if(!masterName[0]) return ENET_SOCKET_NULL;
            if(masterConnection.masterAddress.host == ENET_HOST_ANY)
            {
                if(game::networking::IsDedicatedServer()) logoutf("looking up %s...", masterName);
                masterConnection.masterAddress.port = game::server::MasterPort();
                if(!ResolverWait(masterName, &masterConnection.masterAddress)) return ENET_SOCKET_NULL;
            }
            ENetSocket sock = enet_socket_create(ENET_SOCKET_TYPE_STREAM);
            if(sock == ENET_SOCKET_NULL)
            {
                if(game::networking::IsDedicatedServer()) logoutf("could not open master server socket");
                return ENET_SOCKET_NULL;
            }
            if(wait || masterConnection.serverAddress.host == ENET_HOST_ANY || !enet_socket_bind(sock, &masterConnection.serverAddress))
            {
                enet_socket_set_option(sock, ENET_SOCKOPT_NONBLOCK, 1);
                if(wait)
                {
                    if(!ConnectWithoutTimeout(sock, masterName, masterConnection.masterAddress)) return sock;
                }
                else if(!enet_socket_connect(sock, &masterConnection.masterAddress)) return sock;
            }
            enet_socket_destroy(sock);
            if(game::networking::IsDedicatedServer()) logoutf("could not connect to master server");
            return ENET_SOCKET_NULL;
        }

        void DisconnectMaster()
        {
            if(masterConnection.masterSock != ENET_SOCKET_NULL)
            {
                game::server::MasterDisconnected();
                enet_socket_destroy(masterConnection.masterSock);
                masterConnection.masterSock = ENET_SOCKET_NULL;
            }

            masterConnection.masterOut.setsize(0);
            masterConnection.masterIn.setsize(0);
            masterConnection.masterOutPos = masterConnection.masterInPos = 0;

            masterConnection.masterAddress.host = ENET_HOST_ANY;
            masterConnection.masterAddress.port = ENET_PORT_ANY;

            masterConnection.lastUpdateMaster = 0;
            masterConnection.masterConnecting = 0;
            masterConnection.masterConnected = 0;
        }

        bool RequestMaster(const char *req)
        {
            if(masterConnection.masterSock == ENET_SOCKET_NULL)
            {
                masterConnection.masterSock = ConnectMaster(false);
                if(masterConnection.masterSock == ENET_SOCKET_NULL) 
                    return false;
                masterConnection.lastConnectMaster = masterConnection.masterConnecting = ftsClient.totalMilliseconds ? ftsClient.totalMilliseconds : 1;
            }

            if(masterConnection.masterOut.length() >= 4096) 
                return false;

            masterConnection.masterOut.put(req, strlen(req));

            return true;
        }

        bool RequestMasterf(const char *fmt, ...)
        {
            defvformatcubestr(req, fmt, fmt);
            return RequestMaster(req);
        }

        void ProcessMasterInput()
        {
            if(masterConnection.masterInPos >= masterConnection.masterIn.length()) return;

            char *input = &masterConnection.masterIn[masterConnection.masterInPos], *end = (char *)memchr(input, '\n', masterConnection.masterIn.length() - masterConnection.masterInPos);
            while(end)
            {
                *end = '\0';

                const char *args = input;
                while(args < end && !iscubespace(*args)) args++;
                int cmdlen = args - input;
                while(args < end && iscubespace(*args)) args++;

                if(matchcubestr(input, cmdlen, "failreg"))
                    conoutf(CON_ERROR, "master server registration failed: %s", args);
                else if(matchcubestr(input, cmdlen, "succreg"))
                    conoutf("master server registration succeeded");
                else game::server::ProcessMasterInput(input, cmdlen, args);

                end++;
                masterConnection.masterInPos = end - masterConnection.masterIn.getbuf();
                input = end;
                end = (char *)memchr(input, '\n', masterConnection.masterIn.length() - masterConnection.masterInPos);
            }

            if(masterConnection.masterInPos >= masterConnection.masterIn.length()) {
                masterConnection.masterIn.setsize(0);
                masterConnection.masterInPos = 0;
            }
        }

        void FlushMasterOutput()
        {
            if(masterConnection.masterConnecting && ftsClient.totalMilliseconds - masterConnection.masterConnecting >= 60000)
            {
                logoutf("could not connect to master server");
                DisconnectMaster();
            }
            if(masterConnection.masterOut.empty() || !masterConnection.masterConnected) return;

            ENetBuffer buf;
            buf.data = &masterConnection.masterOut[masterConnection.masterOutPos];
            buf.dataLength = masterConnection.masterOut.length() - masterConnection.masterOutPos;
            int sent = enet_socket_send(masterConnection.masterSock, NULL, &buf, 1);
            if(sent >= 0)
            {
                masterConnection.masterOutPos += sent;
                if(masterConnection.masterOutPos >= masterConnection.masterOut.length())
                {
                    masterConnection.masterOut.setsize(0);
                    masterConnection.masterOutPos = 0;
                }
            } else {
                DisconnectMaster();
            }
        }

        void FlushMasterInput()
        {
            if(masterConnection.masterIn.length() >= masterConnection.masterIn.capacity())
                masterConnection.masterIn.reserve(4096);

            ENetBuffer buf;
            buf.data = masterConnection.masterIn.getbuf() + masterConnection.masterIn.length();
            buf.dataLength = masterConnection.masterIn.capacity() - masterConnection.masterIn.length();
            int recv = enet_socket_receive(masterConnection.masterSock, NULL, &buf, 1);
            if(recv > 0)
            {
                masterConnection.masterIn.advance(recv);
                ProcessMasterInput();
            }
            else {
                DisconnectMaster();
            }
        };

        static ENetAddress serverInfoAddress;

        void SendServerInfoReply(ucharbuf &p)
        {
            ENetBuffer buf;
            buf.data = p.buf;
            buf.dataLength = p.length();
            enet_socket_send(hostServerInfo.serverHost->socket, &serverInfoAddress, &buf, 1);
        }

        #define MAXPINGDATA 32

        void CheckServerSockets()        // reply all server info requests
        {
            static ENetSocketSet readset, writeset;
            ENET_SOCKETSET_EMPTY(readset);
            ENET_SOCKETSET_EMPTY(writeset);
            ENetSocket maxSock = ENET_SOCKET_NULL;
            if(masterConnection.masterSock != ENET_SOCKET_NULL)
            {
                maxSock = maxSock == ENET_SOCKET_NULL ? masterConnection.masterSock : max(masterConnection.masterSock, maxSock);
                ENET_SOCKETSET_ADD(readset, masterConnection.masterSock);
                if(!masterConnection.masterConnected) ENET_SOCKETSET_ADD(writeset, masterConnection.masterSock);
            }
            if(hostServerInfo.lanSock != ENET_SOCKET_NULL)
            {
                maxSock = maxSock == ENET_SOCKET_NULL ? hostServerInfo.lanSock : max(maxSock, hostServerInfo.lanSock);
                ENET_SOCKETSET_ADD(readset, hostServerInfo.lanSock);
            }
            if(maxSock == ENET_SOCKET_NULL || enet_socketset_select(maxSock, &readset, &writeset, 0) <= 0) return;

            if(hostServerInfo.lanSock != ENET_SOCKET_NULL && ENET_SOCKETSET_CHECK(readset, hostServerInfo.lanSock))
            {
                ENetBuffer buf;
                uchar data[MAXTRANS];
                buf.data = data;
                buf.dataLength = sizeof(data);
                int len = enet_socket_receive(hostServerInfo.lanSock, &serverInfoAddress, &buf, 1);
                if(len < 2 || data[0] != 0xFF || data[1] != 0xFF || len-2 > MAXPINGDATA) return;
                ucharbuf req(data+2, len-2), p(data+2, sizeof(data)-2);
                p.len += len-2;
                game::server::ServerInfoReply(req, p);
            }

            if(masterConnection.masterSock != ENET_SOCKET_NULL)
            {
                if(!masterConnection.masterConnected)
                {
                    if(ENET_SOCKETSET_CHECK(readset, masterConnection.masterSock) || ENET_SOCKETSET_CHECK(writeset,  masterConnection.masterSock))
                    {
                        int error = 0;
                        if(enet_socket_get_option(masterConnection.masterSock, ENET_SOCKOPT_ERROR, &error) < 0 || error)
                        {
                            logoutf("could not connect to master server");
                            DisconnectMaster();
                        }
                        else
                        {
                            masterConnection.masterConnecting = 0;
                            masterConnection.masterConnected = ftsClient.totalMilliseconds ? ftsClient.totalMilliseconds : 1;
                            game::server::MasterDisConnected();
                        }
                    }
                }
                if(masterConnection.masterSock != ENET_SOCKET_NULL && ENET_SOCKETSET_CHECK(readset, masterConnection.masterSock)) FlushMasterInput();
            }
        }

        static int ServerInfoIntercept(ENetHost *host, ENetEvent *event)
        {
            if(host->receivedDataLength < 2 || host->receivedData[0] != 0xFF || host->receivedData[1] != 0xFF || host->receivedDataLength-2 > MAXPINGDATA) return 0;
            serverInfoAddress = host->receivedAddress;
            ucharbuf req(host->receivedData+2, host->receivedDataLength-2), p(host->receivedData+2, sizeof(host->packetData[0])-2);
            p.len += host->receivedDataLength-2;
            game::server::ServerInfoReply(req, p);
            return 1;
        }
        };
  
        VAR(serveruprate, 0, 0, INT_MAX);
        SVAR(serverip, "");
        VARF(serverport, 0, game::server::ServerPort(), 0xFFFF, { if(!serverport) serverport = game::server::ServerPort(); });

        #ifdef STANDALONE
        FrameTimeState ftsClient;
        #endif

        void UpdateMasterServer()
        {
            if(!masterConnection.masterConnected && masterConnection.lastConnectMaster && ftsClient.totalMilliseconds-masterConnection.lastConnectMaster <= 5*60*1000) return;
            if(networking::masterName[0] && allowUpdateMaster) networking::RequestMasterf("regserv %d\n", serverport);
            masterConnection.lastUpdateMaster = ftsClient.totalMilliseconds ? ftsClient.totalMilliseconds : 1;
        }

        uint totalsecs = 0;

        void UpdateTime()
        {
            static int lastSecond = 0;
            if(ftsClient.totalMilliseconds - lastSecond >= 1000)
            {
                int currentSecond = (ftsClient.totalMilliseconds - ftsClient.lastMilliseconds) / 1000;
                ftsClient.totalSeconds += currentSecond;
                lastSecond += currentSecond * 1000;
            }
        }

        void ServerSlice(bool dedicated, uint timeout)   // main server update, called from main loop in sp, or from below in dedicated server
        {
            if(!hostServerInfo.serverHost)
            {
                game::server::ServerUpdate();
                game::server::SendPackets();
                return;
            }

            // below is network only

            if(dedicated)
            {
                int millis = (int)enet_time_get();
                ftsClient.elapsedTime = millis - ftsClient.totalMilliseconds;
                static int timeerr = 0;
                int scaledtime = game::server::ScaleTime(ftsClient.elapsedTime) + timeerr;
                ftsClient.currentTime = scaledtime/100;
                timeerr = scaledtime%100;
                if(game::server::IsPaused()) ftsClient.currentTime = 0;
                ftsClient.lastMilliseconds += ftsClient.currentTime;
                ftsClient.totalMilliseconds = millis;
                UpdateTime();
            }
            game::server::ServerUpdate();

            networking::FlushMasterOutput();
            networking::CheckServerSockets();

            if(!masterConnection.lastUpdateMaster || ftsClient.totalMilliseconds-masterConnection.lastUpdateMaster>60*60*1000)       // send alive signal to masterserver every hour of uptime
                UpdateMasterServer();

            if(ftsClient.totalMilliseconds-hostServerInfo.lastStatus>60*1000)   // display bandwidth stats, useful for server ops
            {
                hostServerInfo.lastStatus = ftsClient.totalMilliseconds;
                if(hostServerInfo.nonLocalClients || hostServerInfo.serverHost->totalSentData || hostServerInfo.serverHost->totalReceivedData) logoutf("status: %d remote clients, %.1f send, %.1f rec (K/sec)", hostServerInfo.nonLocalClients, hostServerInfo.serverHost->totalSentData/60.0f/1024, hostServerInfo.serverHost->totalReceivedData/60.0f/1024);
                hostServerInfo.serverHost->totalSentData = hostServerInfo.serverHost->totalReceivedData = 0;
            }

            ENetEvent event;
            bool serviced = false;
            while(!serviced)
            {
                if(enet_host_check_events(hostServerInfo.serverHost, &event) <= 0)
                {
                    if(enet_host_service(hostServerInfo.serverHost, &event, timeout) <= 0) break;
                    serviced = true;
                }
                switch(event.type)
                {
                    case ENET_EVENT_TYPE_CONNECT:
                    {
                        game::networking::ServerClient &c = AddClient(game::networking::ServerState::TcpIP);
                        c.peer = event.peer;
                        c.peer->data = &c;
                        cubestr hn;
                        copycubestr(c.hostName, (enet_address_get_host_ip(&c.peer->address, hn, sizeof(hn))==0) ? hn : "unknown");
                        logoutf("client connected (%s)", c.hostName);
                        game::networking::protocol::DisconnectReason reason = static_cast<game::networking::protocol::DisconnectReason>(game::server::ClientConnect(c.clientNumber, c.peer->address.host));
                        if(static_cast<bool>(reason)) game::networking::Disconnect_Client(c.clientNumber, reason);
                        break;
                    }
                    case ENET_EVENT_TYPE_RECEIVE:
                    {
                        game::networking::ServerClient *c = (game::networking::ServerClient *)event.peer->data;
                        if(c) ::Process(event.packet, c->clientNumber, event.channelID);
                        if(event.packet->referenceCount==0) enet_packet_destroy(event.packet);
                        break;
                    }
                    case ENET_EVENT_TYPE_DISCONNECT:
                    {
                        game::networking::ServerClient *c = (game::networking::ServerClient *)event.peer->data;
                        if(!c) break;
                        logoutf("dIsConnected client (%s)", c->hostName);
                        game::server::ClientDisconnect(c->clientNumber);
                        DelClient(c);
                        break;
                    }
                    default:
                        break;
                }
            }
            if(game::server::SendPackets()) enet_host_flush(hostServerInfo.serverHost);
        }

        void FlushServer(bool force)
        {
            if(game::server::SendPackets(force) && hostServerInfo.serverHost) enet_host_flush(hostServerInfo.serverHost);
        }
  
        #ifndef STANDALONE

        void LocalDisconnect(bool cleanup)
        {
            bool _IsConnected = false;
            loopv(game::server::clients) if(game::server::clients[i]->type==game::networking::ServerState::Local)
            {
                game::server::LocalDisconnect(i);
                DelClient(game::server::clients[i]);
                _IsConnected = true;
            }
            if(!_IsConnected) return;
            game::GameDisconnect(cleanup);
            mainmenu = 1;
        }

        void LocalConnect()
        {
            game::networking::ServerClient &c = AddClient(game::networking::ServerState::Local);
            copycubestr(c.hostName, "local");
            game::client::GameConnect(false);
            game::server::LocalConnect(c.clientNumber);
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

    static bool dedicatedServer = false;

    bool IsDedicatedServer() { 
        return dedicatedServer; 
    }

    void RunDedicatedServer()
    {
        dedicatedServer = true;
        logoutf("dedicated server started, waiting for clients...");
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
            ServerSlice(true, 5);
        }
    #else
        for(;;) ServerSlice(true, 5);
    #endif
        dedicatedServer = false;
    }

    bool ServerError(bool dedicated, const char *desc)
    {
    #ifndef STANDALONE
        if(!dedicated)
        {
            conoutf(CON_ERROR, "%s", desc);
            CleanupServer();
        }
        else
    #endif
            fatal("%s", desc);
        return false;
    }

    bool SetupListenServer(bool dedicated)
    {
        ENetAddress address = { ENET_HOST_ANY, enet_uint16(serverport <= 0 ? game::server::ServerPort() : serverport) };
        if(*serverip)
        {
            if(enet_address_set_host(&address, serverip)<0) conoutf(CON_WARN, "WARNING: server ip not resolved");
            else masterConnection.serverAddress.host = address.host;
        }
        hostServerInfo.serverHost = enet_host_create(&address, min(maxclients + game::server::ReserveClients(), MAXCLIENTS), game::server::GetNumChannels(), 0, serveruprate);
        if(!hostServerInfo.serverHost) return ServerError(dedicated, "could not create server host");
        hostServerInfo.serverHost->duplicatePeers = maxdupclients ? maxdupclients : MAXCLIENTS;
        hostServerInfo.serverHost->intercept = networking::ServerInfoIntercept;
        address.port = game::server::LanInfoPort();
        hostServerInfo.lanSock = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM);
        if(hostServerInfo.lanSock != ENET_SOCKET_NULL && (enet_socket_set_option(hostServerInfo.lanSock, ENET_SOCKOPT_REUSEADDR, 1) < 0 || enet_socket_bind(hostServerInfo.lanSock, &address) < 0))
        {
            enet_socket_destroy(hostServerInfo.lanSock);
            hostServerInfo.lanSock = ENET_SOCKET_NULL;
        }
        if(hostServerInfo.lanSock == ENET_SOCKET_NULL) conoutf(CON_WARN, "WARNING: could not create LAN server info socket");
        else enet_socket_set_option(hostServerInfo.lanSock, ENET_SOCKOPT_NONBLOCK, 1);
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
            dedicatedServer = dedicated;
            UpdateMasterServer();
            if(dedicated) RunDedicatedServer(); // never returns
    #ifndef STANDALONE
            else conoutf("Listen server started");
    #endif
        }
    }

    #ifndef STANDALONE
    SCRIPTEXPORT_AS(startlistenserver) void StartListenserver(int *usemaster)
    {
        if(hostServerInfo.serverHost) { conoutf(CON_ERROR, "Listen server is already running"); return; }

        allowUpdateMaster = *usemaster>0 ? 1 : 0;

        if(!SetupListenServer(false)) return;

        UpdateMasterServer();

        conoutf("Listen server started for %d clients%s", maxclients, allowUpdateMaster ? " and listed with master server" : "");
    }

    SCRIPTEXPORT_AS(stoplistenserver) void StopListenServer()
    {
        if(!hostServerInfo.serverHost) { conoutf(CON_ERROR, "Listen server is not running"); return; }

        game::networking::KickNonLocalclients(game::networking::protocol::DisconnectReason::Local);
        enet_host_flush(hostServerInfo.serverHost);
        CleanupServer();

        conoutf("Listen server stopped");
    }
    #endif

    bool ServerOption(char *opt)
    {
        switch(opt[1])
        {
    #ifdef STANDALONE
            case 'u': logoutf("Using home directory: %s", opt); sethomedir(opt+2); return true;
            case 'k': logoutf("Adding package directory: %s", opt); addpackagedir(opt+2); return true;
            case 'g': logoutf("Setting log file: %s", opt); setlogfile(opt+2); return true;
    #endif
            default: return false;
        }
    }

#ifdef STANDALONE
    vector<const char *> gameargs;
    int main(int argc, char **argv)
    {
        setlogfile(NULL);
        if(enet_initialize()<0) fatal("Unable to initialise network module");
        atexit(enet_deinitialize);
        enet_time_set(0);
        for(int i = 1; i<argc; i++) if(argv[i][0]!='-' || !serveroption(argv[i])) gameargs.add(argv[i]);
        game::parseoptions(gameargs);
        initserver(true, true);
        return EXIT_SUCCESS;
    }
#endif
    };

// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
#if 0
#include "/Users/micha/dev/ScMaMike/src/build/binding/..+engine+server.binding.cpp"
#endif
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
