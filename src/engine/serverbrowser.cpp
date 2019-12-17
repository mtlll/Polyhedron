#include "engine.h"

#include "game/server/server.h"
#include "game/client/client.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/protocol.h"

struct resolverthread
{
    SDL_Thread *thread;
    const char *query;
    int starttime;
};

struct resolverresult
{
    const char *query;
    ENetAddress address;
};

vector<resolverthread> resolverthreads;
vector<const char *> resolverqueries;
vector<resolverresult> resolverresults;
SDL_mutex *resolvermutex;
SDL_cond *querycond, *resultcond;

#define RESOLVERTHREADS 2
#define RESOLVERLIMIT 3000

int resolverloop(void * data)
{
    resolverthread *rt = (resolverthread *)data;
    SDL_LockMutex(resolvermutex);
    SDL_Thread *thread = rt->thread;
    SDL_UnlockMutex(resolvermutex);
    if(!thread || SDL_GetThreadID(thread) != SDL_ThreadID())
        return 0;
    while(thread == rt->thread)
    {
        SDL_LockMutex(resolvermutex);
        while(resolverqueries.empty()) SDL_CondWait(querycond, resolvermutex);
        rt->query = resolverqueries.pop();
        rt->starttime = ftsClient.totalMilliseconds;
        SDL_UnlockMutex(resolvermutex);

        ENetAddress address = { ENET_HOST_ANY, ENET_PORT_ANY };
        enet_address_set_host(&address, rt->query);

        SDL_LockMutex(resolvermutex);
        if(rt->query && thread == rt->thread)
        {
            resolverresult &rr = resolverresults.add();
            rr.query = rt->query;
            rr.address = address;
            rt->query = NULL;
            rt->starttime = 0;
            SDL_CondSignal(resultcond);
        }
        SDL_UnlockMutex(resolvermutex);
    }
    return 0;
}

void resolverinit()
{
    resolvermutex = SDL_CreateMutex();
    querycond = SDL_CreateCond();
    resultcond = SDL_CreateCond();

    SDL_LockMutex(resolvermutex);
    loopi(RESOLVERTHREADS)
    {
        resolverthread &rt = resolverthreads.add();
        rt.query = NULL;
        rt.starttime = 0;
        rt.thread = SDL_CreateThread(resolverloop, "resolver", &rt);
    }
    SDL_UnlockMutex(resolvermutex);
}

void resolverstop(resolverthread &rt)
{
    SDL_LockMutex(resolvermutex);
    if(rt.query)
    {
#if SDL_VERSION_ATLEAST(2, 0, 2)
        SDL_DetachThread(rt.thread);
#endif
        rt.thread = SDL_CreateThread(resolverloop, "resolver", &rt);
    }
    rt.query = NULL;
    rt.starttime = 0;
    SDL_UnlockMutex(resolvermutex);
}

void resolverclear()
{
    if(resolverthreads.empty()) return;

    SDL_LockMutex(resolvermutex);
    resolverqueries.shrink(0);
    resolverresults.shrink(0);
    loopv(resolverthreads)
    {
        resolverthread &rt = resolverthreads[i];
        resolverstop(rt);
    }
    SDL_UnlockMutex(resolvermutex);
}

void resolverquery(const char *name)
{
    if(resolverthreads.empty()) resolverinit();

    SDL_LockMutex(resolvermutex);
    resolverqueries.add(name);
    SDL_CondSignal(querycond);
    SDL_UnlockMutex(resolvermutex);
}

bool resolvercheck(const char **name, ENetAddress *address)
{
    bool resolved = false;
    SDL_LockMutex(resolvermutex);
    if(!resolverresults.empty())
    {
        resolverresult &rr = resolverresults.pop();
        *name = rr.query;
        address->host = rr.address.host;
        resolved = true;
    }
    else loopv(resolverthreads)
    {
        resolverthread &rt = resolverthreads[i];
        if(rt.query && ftsClient.totalMilliseconds - rt.starttime > RESOLVERLIMIT)
        {
            resolverstop(rt);
            *name = rt.query;
            resolved = true;
        }
    }
    SDL_UnlockMutex(resolvermutex);
    return resolved;
}

bool resolverwait(const char *name, ENetAddress *address)
{
    if(resolverthreads.empty()) resolverinit();

    defformatcubestr(text, "resolving %s... (esc to abort)", name);
    renderprogress(0, text);

    SDL_LockMutex(resolvermutex);
    resolverqueries.add(name);
    SDL_CondSignal(querycond);
    int starttime = SDL_GetTicks(), timeout = 0;
    bool resolved = false;
    for(;;)
    {
        SDL_CondWaitTimeout(resultcond, resolvermutex, 250);
        loopv(resolverresults) if(resolverresults[i].query == name)
        {
            address->host = resolverresults[i].address.host;
            resolverresults.remove(i);
            resolved = true;
            break;
        }
        if(resolved) break;

        timeout = SDL_GetTicks() - starttime;
        renderprogress(min(float(timeout)/RESOLVERLIMIT, 1.0f), text);
        if(interceptkey(SDLK_ESCAPE)) timeout = RESOLVERLIMIT + 1;
        if(timeout > RESOLVERLIMIT) break;
    }
    if(!resolved && timeout > RESOLVERLIMIT)
    {
        loopv(resolverthreads)
        {
            resolverthread &rt = resolverthreads[i];
            if(rt.query == name) { resolverstop(rt); break; }
        }
    }
    SDL_UnlockMutex(resolvermutex);
    return resolved;
}

#define CONNLIMIT 20000

int connectwithtimeout(ENetSocket sock, const char *hostname, const ENetAddress &address)
{
    defformatcubestr(text, "connecting to %s... (esc to abort)", hostname);
    renderprogress(0, text);

    ENetSocketSet readset, writeset;
    if(!enet_socket_connect(sock, &address)) for(int starttime = SDL_GetTicks(), timeout = 0; timeout <= CONNLIMIT;)
    {
        ENET_SOCKETSET_EMPTY(readset);
        ENET_SOCKETSET_EMPTY(writeset);
        ENET_SOCKETSET_ADD(readset, sock);
        ENET_SOCKETSET_ADD(writeset, sock);
        int result = enet_socketset_select(sock, &readset, &writeset, 250);
        if(result < 0) break;
        else if(result > 0)
        {
            if(ENET_SOCKETSET_CHECK(readset, sock) || ENET_SOCKETSET_CHECK(writeset, sock))
            {
                int error = 0;
                if(enet_socket_get_option(sock, ENET_SOCKOPT_ERROR, &error) < 0 || error) break;
                return 0;
            }
        }
        timeout = SDL_GetTicks() - starttime;
        renderprogress(min(float(timeout)/CONNLIMIT, 1.0f), text);
        if(interceptkey(SDLK_ESCAPE)) break;
    }

    return -1;
}

namespace game { 
    namespace networking {
        struct BrowserPingAttempts
        {
        public:
            enum class MaxAttempts : int { 
                Two = 2 
            };

            int offset = 0;
            int attempts[2];

            BrowserPingAttempts() {
                ClearAttempts();
            }

            void ClearAttempts() {
                std::memset(attempts, 0, static_cast<std::size_t>(MaxAttempts::Two));
            }

            void SetOffset() {
                offset = 1 + rnd(0xFFFFFF);
            }

            int EncodePing(int millis) {
                millis += offset;
                return millis ? millis : 1;
            }

            int DecodePing(int val) {
                return val - offset;
            }

            int AddAttempt(int millis) {
                int val = EncodePing(millis);
                loopk(static_cast<int>(MaxAttempts::Two)-1) attempts[k+1] = attempts[k];
                attempts[0] = val;
                return val;
            }

            bool CheckAttempt(int val, bool del = true) {
                if(val) loopk(static_cast<int>(MaxAttempts::Two)) if(attempts[k] == val)
                {
                    if(del) attempts[k] = 0;
                    return true;
                }
                return false;
            }
        };
    };


static int currentProtocol = game::server::ProtocolVersion();

enum { UNRESOLVED = 0, RESOLVING, RESOLVED };

struct BrowserServerInfo : public game::networking::BrowserPingAttempts, public game::networking::ServerInfo, public game::networking::ServerClient
{
    enum
    {
        WAITING = INT_MAX,

        MAXPINGS = 3
    };

    int resolved, lastPing, nextPing;
    int pings[MAXPINGS];
    ENetAddress address;
    bool keep;
    const char *password;

    BrowserServerInfo()
     : resolved(UNRESOLVED), keep(false), password(NULL)
    {
        ClearPings();
        SetOffset();
    }

    ~BrowserServerInfo()
    {
        DELETEA(password);
    }

    void ClearPings()
    {
        ping = WAITING;
        loopk(MAXPINGS) pings[k] = WAITING;
        nextPing = 0;
        lastPing = -1;
        ClearAttempts();
    }

    void CleanUp()
    {
        ClearPings();
        protocol = -1;
        numberOfPlayers = maxPlayers = 0;
        attr.setsize(0);
    }

    void Reset()
    {
        lastPing = -1;
    }

    void CheckDecay(int decay)
    {
        if(lastPing >= 0 && ftsClient.totalMilliseconds - lastPing >= decay)
            CleanUp();
        if(lastPing < 0) lastPing = ftsClient.totalMilliseconds;
    }

    void CalcPing()
    {
        int numPings = 0, totalPings = 0;
        loopk(MAXPINGS) if(pings[k] != WAITING) { totalPings += pings[k]; numPings++; }
        ping = numPings ? totalPings/numPings : WAITING;
    }

    void AddPing(int rtt, int millis)
    {
        if(millis >= lastPing) lastPing = -1;
        pings[nextPing] = rtt;
        nextPing = (nextPing+1)%MAXPINGS;
        CalcPing();
    }

    const char *Status() const
    {
        if(address.host == ENET_HOST_ANY) return "[unknown host]";
        if(ping == WAITING) return "[waiting for response]";
        if(protocol < currentProtocol) return "[older protocol]";
        if(protocol > currentProtocol) return "[newer protocol]";
        return NULL;
    }

    bool valid() const { return !Status(); }

    static bool Compare(BrowserServerInfo *a, BrowserServerInfo *b)
    {
        if(a->protocol == currentProtocol)
        {
            if(b->protocol != currentProtocol) return true;
        }
        else if(b->protocol == currentProtocol) return false;
        if(a->keep > b->keep) return true;
        if(a->keep < b->keep) return false;
        if(a->numberOfPlayers < b->numberOfPlayers) return false;
        if(a->numberOfPlayers > b->numberOfPlayers) return true;
        if(a->ping > b->ping) return false;
        if(a->ping < b->ping) return true;
        int cmp = strcmp(a->name, b->name);
        if(cmp != 0) return cmp < 0;
        if(a->address.port < b->address.port) return true;
        if(a->address.port > b->address.port) return false;
        return false;
    }
};

vector<BrowserServerInfo *> browserServers;
ENetSocket browserPingSock = ENET_SOCKET_NULL;
BrowserServerInfo browserLanPings;
int browserLastInfo = 0;

static BrowserServerInfo *NewServer(const char *name, int port, uint ip = ENET_HOST_ANY)
{
    BrowserServerInfo *si = new BrowserServerInfo;
    si->address.host = ip;
    si->address.port = port;
    if(ip!=ENET_HOST_ANY) si->resolved = RESOLVED;

    if(name) copycubestr(si->name, name);
    else if(ip==ENET_HOST_ANY || enet_address_get_host_ip(&si->address, si->name, sizeof(si->name)) < 0)
    {
        delete si;
        return NULL;

    }

    browserServers.add(si);

    return si;
}

void AddServer(const char *name, int port, const char *password, bool keep = true)
{
    if(port <= 0) port = game::server::ServerPort();
    loopv(browserServers)
    {
        BrowserServerInfo *s = browserServers[i];
        if(strcmp(s->name, name) || s->address.port != port) continue;
        if(password && (!s->password || strcmp(s->password, password)))
        {
            DELETEA(s->password);
            s->password = newcubestr(password);
        }
        if(keep && !s->keep) s->keep = true;
        return;
    }
    BrowserServerInfo *s = NewServer(name, port);
    if(!s) return;
    if(password) s->password = newcubestr(password);
    s->keep = keep;
}

VARP(searchlan, 0, 0, 1);
VARMP(servpingrate, 1, 5, 60, 1000);
VARMP(servpingdecay, 1, 15, 60, 1000);
VARP(maxservpings, 0, 10, 1000);

game::networking::BrowserPingAttempts lanPings;

template<size_t N> static inline void BuildPing(ENetBuffer &buf, uchar (&ping)[N], game::networking::BrowserPingAttempts &a)
{
    ucharbuf p(ping, N);
    p.put(0xFF); p.put(0xFF);
    game::networking::putint(p, a.AddAttempt(ftsClient.totalMilliseconds));
    buf.data = ping;
    buf.dataLength = p.length();
}

void pingservers()
{
    if(browserPingSock == ENET_SOCKET_NULL)
    {
        browserPingSock = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM);
        if(browserPingSock == ENET_SOCKET_NULL)
        {
            browserLastInfo = ftsClient.totalMilliseconds;
            return;
        }
        enet_socket_set_option(browserPingSock, ENET_SOCKOPT_NONBLOCK, 1);
        enet_socket_set_option(browserPingSock, ENET_SOCKOPT_BROADCAST, 1);

        lanPings.SetOffset();
    }

    ENetBuffer buf;
    uchar ping[MAXTRANS];

    static int lastPing = 0;
    if(lastPing >= browserServers.length()) lastPing = 0;
    loopi(maxservpings ? min(browserServers.length(), maxservpings) : browserServers.length())
    {
        BrowserServerInfo &si = *browserServers[lastPing];
        if(++lastPing >= browserServers.length()) lastPing = 0;
        if(si.address.host == ENET_HOST_ANY) continue;
        BuildPing(buf, ping, si);
        enet_socket_send(browserPingSock, &si.address, &buf, 1);

        si.CheckDecay(servpingdecay);
    }
    if(searchlan)
    {
        ENetAddress address;
        address.host = ENET_HOST_BROADCAST;
        address.port = game::server::LanInfoPort();
        BuildPing(buf, ping, browserLanPings);
        enet_socket_send(browserPingSock, &address, &buf, 1);
    }
    browserLastInfo = ftsClient.totalMilliseconds;
}

void checkresolver()
{
    int resolving = 0;
    loopv(browserServers)
    {
        BrowserServerInfo &si = *browserServers[i];
        if(si.resolved == RESOLVED) continue;
        if(si.address.host == ENET_HOST_ANY)
        {
            if(si.resolved == UNRESOLVED) { si.resolved = RESOLVING; resolverquery(si.name); }
            resolving++;
        }
    }
    if(!resolving) return;

    const char *name = NULL;
    for(;;)
    {
        ENetAddress addr = { ENET_HOST_ANY, ENET_PORT_ANY };
        if(!resolvercheck(&name, &addr)) break;
        loopv(browserServers)
        {
            BrowserServerInfo &si = *browserServers[i];
            if(name == si.name)
            {
                si.resolved = RESOLVED;
                si.address.host = addr.host;
                break;
            }
        }
    }
}

static int lastreset = 0;

void CheckPings()
{
    if(browserPingSock==ENET_SOCKET_NULL) return;
    enet_uint32 events = ENET_SOCKET_WAIT_RECEIVE;
    ENetBuffer buf;
    ENetAddress addr;
    uchar ping[MAXTRANS];
    char text[MAXTRANS];
    buf.data = ping;
    buf.dataLength = sizeof(ping);
    while(enet_socket_wait(browserPingSock, &events, 0) >= 0 && events)
    {
        int len = enet_socket_receive(browserPingSock, &addr, &buf, 1);
        if(len <= 0) return;
        ucharbuf p(ping, len);
        int millis = game::networking::getint(p);
        BrowserServerInfo *si = NULL;
        loopv(browserServers) if(addr.host == browserServers[i]->address.host && addr.port == browserServers[i]->address.port) { si = browserServers[i]; break; }
        if(si)
        {
            if(!si->CheckAttempt(millis)) continue;
            millis = si->DecodePing(millis);
        }
        else if(!searchlan || !lanPings.CheckAttempt(millis, false)) continue;
        else
        {
            si = NewServer(NULL, addr.port, addr.host);
            millis = lanPings.DecodePing(millis);
        }
        int rtt = clamp(ftsClient.totalMilliseconds - millis, 0, min(servpingdecay, ftsClient.totalMilliseconds));
        if(millis >= lastreset && rtt < servpingdecay) si->AddPing(rtt, millis);
        si->protocol = game::networking::getint(p);
        si->numberOfPlayers = game::networking::getint(p);
        si->maxPlayers = game::networking::getint(p);
        int numattr = game::networking::getint(p);
        si->attr.setsize(0);
        loopj(numattr) { int attr = game::networking::getint(p); if(p.overread()) break; si->attr.add(attr); }
        game::networking::getcubestr(text, p);
        game::networking::filtertext<260>(si->map, text, false);
        game::networking::getcubestr(text, p);
        game::networking::filtertext<260>(si->desc, text);
    }
}

SCRIPTEXPORT void sortservers()
{
    browserServers.sort(BrowserServerInfo::Compare);
}

VARP(autosortservers, 0, 1, 1);
VARP(autoupdateservers, 0, 1, 1);

SCRIPTEXPORT_AS(refreshservers) void RefreshServers()
{
    static int lastrefresh = 0;
    if(lastrefresh==ftsClient.totalMilliseconds) return;
    if(ftsClient.totalMilliseconds - lastrefresh > 1000)
    {
        loopv(browserServers) browserServers[i]->Reset();
        lastreset = ftsClient.totalMilliseconds;
    }
    lastrefresh = ftsClient.totalMilliseconds;

    checkresolver();
    CheckPings();
    if(ftsClient.totalMilliseconds - browserLastInfo >= servpingrate/(maxservpings ? max(1, (browserServers.length() + maxservpings - 1) / maxservpings) : 1)) pingservers();
    if(autosortservers) sortservers();
}

SCRIPTEXPORT void NumServers()
{
    intret(browserServers.length());
}

#define GETSERVERINFO_(idx, si, body) \
    if(browserServers.inrange(idx)) \
    { \
        BrowserServerInfo &si = *browserServers[idx]; \
        body; \
    }
#define GETSERVERINFO(idx, si, body) GETSERVERINFO_(idx, si, if(si.valid()) { body; })

SCRIPTEXPORT_AS(servinfovalid) void ServerInfoValid(int *i)
{
    GETSERVERINFO_(*i, si, intret(si.valid() ? 1 : 0));
}

SCRIPTEXPORT_AS(servinfodesc) void ServerInfoDescription(int *i)
{
    GETSERVERINFO_(*i, si,
    {
        const char *status = si.Status();
        result(status ? status : si.desc);
    });
}

SCRIPTEXPORT_AS(servinfoname) void ServerInfoName(int *i)
{
    GETSERVERINFO_(*i, si, result(si.name));
}

SCRIPTEXPORT_AS(servinfoport) void ServInfoPort(int *i)
{
    GETSERVERINFO_(*i, si, intret(si.address.port));
}

SCRIPTEXPORT_AS(servinfohaspassword) void ServerInfoHasPassword(int *i)
{
    GETSERVERINFO_(*i, si, intret(si.password && si.password[0] ? 1 : 0));
}

SCRIPTEXPORT_AS(servinfokeep) void ServerInfoKeep(int *i)
{
    GETSERVERINFO_(*i, si, intret(si.keep ? 1 : 0));
}

SCRIPTEXPORT_AS(servinfomap) void ServerInfoMap(int *i)
{
    GETSERVERINFO(*i, si, result(si.map));
}

SCRIPTEXPORT_AS(servinfoping) void ServerInfoPing(int *i)
{
    GETSERVERINFO(*i, si, intret(si.ping));
}

SCRIPTEXPORT_AS(servinfonumberOfPlayers) void ServerInfoNumberOfPlayers(int *i)
{
    GETSERVERINFO(*i, si, intret(si.numberOfPlayers));
}

SCRIPTEXPORT_AS(servinfomaxPlayers) void ServerInfoMaxPlayers(int *i)
{
    GETSERVERINFO(*i, si, intret(si.maxPlayers));
}

SCRIPTEXPORT_AS(servinfoplayers) void ServerInfoPlayers(int *i)
{
    GETSERVERINFO(*i, si,
    {
        if(si.maxPlayers <= 0) intret(si.numberOfPlayers);
        else result(tempformatcubestr(si.numberOfPlayers >= si.maxPlayers ? "\f3%d/%d" : "%d/%d", si.numberOfPlayers, si.maxPlayers));
    });
}

SCRIPTEXPORT_AS(servinfoattr) void ServerInfoAttribute(int *i, int *n)
{
    GETSERVERINFO(*i, si, { if(si.attr.inrange(*n)) intret(si.attr[*n]); });
}

SCRIPTEXPORT_AS(connectservinfo) void ConnectServinfo(int *i, char *pw)
{
    GETSERVERINFO_(*i, si, ConnectServ(si.name, si.address.port, pw[0] ? pw : si.password));
}

// game::networking::BrowserServerInfo *::GetServerInfo(int i)
// {
//     return browserServers.inrange(i) && browserServers[i]->Valid() ? browserServers[i] : NULL;
// }

void ClearServers(bool full = false)
{
    resolverclear();
    if(full) browserServers.deletecontents();
    else loopvrev(browserServers) if(!browserServers[i]->keep) delete browserServers.remove(i);
}

#define RETRIEVELIMIT 20000

void RetrieveServers(vector<char> &data)
{
    ENetSocket sock = ConnectMaster(true);
    if(sock == ENET_SOCKET_NULL) return;

    extern char *masterName;
    defformatcubestr(text, "retrieving servers from %s... (esc to abort)", masterName);
    ::renderprogress(0, text);

    int starttime = SDL_GetTicks(), timeout = 0;
    const char *req = "list\n";
    int reqlen = strlen(req);
    ENetBuffer buf;
    while(reqlen > 0)
    {
        enet_uint32 events = ENET_SOCKET_WAIT_SEND;
        if(enet_socket_wait(sock, &events, 250) >= 0 && events)
        {
            buf.data = (void *)req;
            buf.dataLength = reqlen;
            int sent = enet_socket_send(sock, NULL, &buf, 1);
            if(sent < 0) break;
            req += sent;
            reqlen -= sent;
            if(reqlen <= 0) break;
        }
        timeout = SDL_GetTicks() - starttime;
        ::renderprogress(min(float(timeout)/RETRIEVELIMIT, 1.0f), text);
        if(interceptkey(SDLK_ESCAPE)) timeout = RETRIEVELIMIT + 1;
        if(timeout > RETRIEVELIMIT) break;
    }

    if(reqlen <= 0) for(;;)
    {
        enet_uint32 events = ENET_SOCKET_WAIT_RECEIVE;
        if(enet_socket_wait(sock, &events, 250) >= 0 && events)
        {
            if(data.length() >= data.capacity()) data.reserve(4096);
            buf.data = data.getbuf() + data.length();
            buf.dataLength = data.capacity() - data.length();
            int recv = enet_socket_receive(sock, NULL, &buf, 1);
            if(recv <= 0) break;
            data.advance(recv);
        }
        timeout = SDL_GetTicks() - starttime;
        ::renderprogress(min(float(timeout)/RETRIEVELIMIT, 1.0f), text);
        if(interceptkey(SDLK_ESCAPE)) timeout = RETRIEVELIMIT + 1;
        if(timeout > RETRIEVELIMIT) break;
    }

    if(data.length()) data.add('\0');
    enet_socket_destroy(sock);
}

bool updatedServers = false;

SCRIPTEXPORT_AS(updatefrommaster) void UpdateFromMaster()
{
    vector<char> data;
    RetrieveServers(data);
    if(data.empty()) conoutf("master server not replying");
    else
    {
        ClearServers();
        execute(data.getbuf());
    }
    RefreshServers();
    updatedServers = true;
}

SCRIPTEXPORT_AS(initservers) void InitServers()
{
    if(autoupdateservers && !updatedServers) UpdateFromMaster();
}

SCRIPTEXPORT_AS(addserver) void addserver_scriptimpl(const char *name, int *port, const char *password)
{
    AddServer(name, *port, password[0] ? password : NULL);
}

SCRIPTEXPORT_AS(keepserver) void KeepServer(const char *name, int *port, const char *password)
{
    AddServer(name, *port, password[0] ? password : NULL, true);
}

SCRIPTEXPORT_AS(clearservers) void clearservers_scriptimpl(int *full)
{
    ClearServers(*full!=0);
}

void WriteServerCfg()
{
    if(!game::SavedServersCfg()) return;
    stream *f = openutf8file(path(game::SavedServersCfg(), true), "w");
    if(!f) return;
    int kept = 0;
    loopv(browserServers)
    {
        BrowserServerInfo *s = browserServers[i];
        if(s->keep)
        {
            // Notice how escapeid(CS Variable) function is used, for keepserver.
            if(!kept) f->printf("// servers that should never be cleared from the server list\n\n");
            if(s->password) f->printf("keepserver %s %d %s\n", escapeid(s->name), s->address.port, escapecubestr(s->password));
            else f->printf("keepserver %s %d\n", escapeid(s->name), s->address.port);
            kept++;
        }
    }
    if(kept) f->printf("\n");
    f->printf("// servers connected to are added here automatically\n\n");
    loopv(browserServers)
    {
        BrowserServerInfo *s = browserServers[i];
        if(!s->keep)
        {
            if(s->password) f->printf("addserver %s %d %s\n", escapeid(s->name), s->address.port, escapecubestr(s->password));
            else f->printf("addserver %s %d\n", escapeid(s->name), s->address.port);
        }
    }
    delete f;
}
};

// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
#if 0
#include "/Users/micha/dev/ScMaMike/src/build/binding/..+engine+serverbrowser.binding.cpp"
#endif
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
