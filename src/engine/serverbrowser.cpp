#include "engine.h"

#include "game/game.h"
#include "game/client/client.h"
#include "game/server/server.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/protocol.h"
#include "shared/networking/cl_frametimestate.h"
#include "shared/networking/sv_frametimestate.h"

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
        rt->starttime = shared::network::ftsClient.totalMilliseconds;
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
        if(rt.query && shared::network::ftsClient.totalMilliseconds - rt.starttime > RESOLVERLIMIT)
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

struct PingAttempts
{
    enum { MAXATTEMPTS = 2 };

    int offset, attempts[MAXATTEMPTS];

    PingAttempts() : offset(0) { ClearAttempts(); }

    void ClearAttempts() { memset(attempts, 0, sizeof(attempts)); }

    void SetOffset() { offset = 1 + rnd(0xFFFFFF); }

    int EncodePing(int millis)
    {
        millis += offset;
        return millis ? millis : 1;
    }

    int DecodePing(int val)
    {
        return val - offset;
    }

    int AddAttempt(int millis)
    {
        int val = EncodePing(millis);
        loopk(MAXATTEMPTS-1) attempts[k+1] = attempts[k];
        attempts[0] = val;
        return val;
    }

    bool CheckAttempt(int val, bool del = true)
    {
        if(val) loopk(MAXATTEMPTS) if(attempts[k] == val)
        {
            if(del) attempts[k] = 0;
            return true;
        }
        return false;
    }

};

static int currentprotocol = game::server::ProtocolVersion();

enum { UNRESOLVED = 0, RESOLVING, RESOLVED };

struct ServerInfo : game::server::ServInfo, PingAttempts
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

    ServerInfo()
     : resolved(UNRESOLVED), keep(false), password(NULL)
    {
        ClearPings();
        SetOffset();
    }

    ~ServerInfo()
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

    void Cleanup()
    {
        ClearPings();
        this->protocol = -1;
        numberOfPlayers = maximumOfPlayers = 0;
        attr.setsize(0);
    }

    void Reset()
    {
        lastPing = -1;
    }

    void CheckDecay(int decay)
    {
        if(lastPing >= 0 && shared::network::ftsClient.totalMilliseconds - lastPing >= decay)
            Cleanup();
        if(lastPing < 0) lastPing = shared::network::ftsClient.totalMilliseconds;
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
        if(this->protocol < currentprotocol) return "[older protocol]";
        if(this->protocol > currentprotocol) return "[newer protocol]";
        return NULL;
    }

    bool Valid() const { return !Status(); }

    static bool compare(ServerInfo *a, ServerInfo *b)
    {
        if(a->protocol == currentprotocol)
        {
            if(b->protocol != currentprotocol) return true;
        }
        else if(b->protocol == currentprotocol) return false;
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

vector<ServerInfo *> servers;
ENetSocket pingsock = ENET_SOCKET_NULL;
int lastinfo = 0;

static ServerInfo *newserver(const char *name, int port, uint ip = ENET_HOST_ANY)
{
    ServerInfo *si = new ServerInfo;
    si->address.host = ip;
    si->address.port = port;
    if(ip!=ENET_HOST_ANY) si->resolved = RESOLVED;

    if(name) copycubestr(si->name, name);
    else if(ip==ENET_HOST_ANY || enet_address_get_host_ip(&si->address, si->name, sizeof(si->name)) < 0)
    {
        delete si;
        return NULL;

    }

    servers.add(si);

    return si;
}

void addserver(const char *name, int port, const char *password, bool keep)
{
    if(port <= 0) port = game::server::ServerPort();
    loopv(servers)
    {
        ServerInfo *s = servers[i];
        if(strcmp(s->name, name) || s->address.port != port) continue;
        if(password && (!s->password || strcmp(s->password, password)))
        {
            DELETEA(s->password);
            s->password = newcubestr(password);
        }
        if(keep && !s->keep) s->keep = true;
        return;
    }
    ServerInfo *s = newserver(name, port);
    if(!s) return;
    if(password) s->password = newcubestr(password);
    s->keep = keep;
}

VARP(searchlan, 0, 0, 1);
VARMP(servpingrate, 1, 5, 60, 1000);
VARMP(servpingdecay, 1, 15, 60, 1000);
VARP(maxservpings, 0, 10, 1000);

PingAttempts lanpings;

template<size_t N> static inline void buildping(ENetBuffer &buf, uchar (&ping)[N], PingAttempts &a)
{
    ucharbuf p(ping, N);
    p.put(0xFF); p.put(0xFF);
    shared::network::PutInt(p, a.AddAttempt(shared::network::ftsClient.totalMilliseconds));
    buf.data = ping;
    buf.dataLength = p.length();
}

void pingservers()
{
    if(pingsock == ENET_SOCKET_NULL)
    {
        pingsock = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM);
        if(pingsock == ENET_SOCKET_NULL)
        {
            lastinfo = shared::network::ftsClient.totalMilliseconds;
            return;
        }
        enet_socket_set_option(pingsock, ENET_SOCKOPT_NONBLOCK, 1);
        enet_socket_set_option(pingsock, ENET_SOCKOPT_BROADCAST, 1);

        lanpings.SetOffset();
    }

    ENetBuffer buf;
    uchar ping[MAXTRANS];

    static int lastping = 0;
    if(lastping >= servers.length()) lastping = 0;
    loopi(maxservpings ? min(servers.length(), maxservpings) : servers.length())
    {
        ServerInfo &si = *servers[lastping];
        if(++lastping >= servers.length()) lastping = 0;
        if(si.address.host == ENET_HOST_ANY) continue;
        buildping(buf, ping, si);
        enet_socket_send(pingsock, &si.address, &buf, 1);

        si.CheckDecay(servpingdecay);
    }
    if(searchlan)
    {
        ENetAddress address;
        address.host = ENET_HOST_BROADCAST;
        address.port = game::server::LanInfoPort();
        buildping(buf, ping, lanpings);
        enet_socket_send(pingsock, &address, &buf, 1);
    }
    lastinfo = shared::network::ftsClient.totalMilliseconds;
}

void checkresolver()
{
    int resolving = 0;
    loopv(servers)
    {
        ServerInfo &si = *servers[i];
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
        loopv(servers)
        {
            ServerInfo &si = *servers[i];
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

void checkpings()
{
    if(pingsock==ENET_SOCKET_NULL) return;
    enet_uint32 events = ENET_SOCKET_WAIT_RECEIVE;
    ENetBuffer buf;
    ENetAddress addr;
    uchar ping[MAXTRANS];
    char text[MAXTRANS];
    buf.data = ping;
    buf.dataLength = sizeof(ping);
    while(enet_socket_wait(pingsock, &events, 0) >= 0 && events)
    {
        int len = enet_socket_receive(pingsock, &addr, &buf, 1);
        if(len <= 0) return;
        ucharbuf p(ping, len);
        int millis = shared::network::GetInt(p);
        ServerInfo *si = NULL;
        loopv(servers) if(addr.host == servers[i]->address.host && addr.port == servers[i]->address.port) { si = servers[i]; break; }
        if(si)
        {
            if(!si->CheckAttempt(millis)) continue;
            millis = si->DecodePing(millis);
        }
        else if(!searchlan || !lanpings.CheckAttempt(millis, false)) continue;
        else
        {
            si = newserver(NULL, addr.port, addr.host);
            millis = lanpings.DecodePing(millis);
        }
        int rtt = clamp(shared::network::ftsClient.totalMilliseconds - millis, 0, min(servpingdecay, shared::network::ftsClient.totalMilliseconds));
        if(millis >= lastreset && rtt < servpingdecay) si->AddPing(rtt, millis);
        si->protocol = shared::network::GetInt(p);
        si->numberOfPlayers = shared::network::GetInt(p);
        si->maximumOfPlayers = shared::network::GetInt(p);
        int numattr = shared::network::GetInt(p);
        si->attr.setsize(0);
        loopj(numattr) { int attr = shared::network::GetInt(p); if(p.overread()) break; si->attr.add(attr); }
        shared::network::GetCubeStr<MAXTRANS>(text, p);
        shared::network::FilterText<260>(si->map, text, false, false);
        shared::network::GetCubeStr<MAXTRANS>(text, p);
        shared::network::FilterText<260>(si->desc, text, false, false);
    }
}

SCRIPTEXPORT void sortservers()
{
    servers.sort(ServerInfo::compare);
}

VARP(autosortservers, 0, 1, 1);
VARP(autoupdateservers, 0, 1, 1);

SCRIPTEXPORT void refreshservers()
{
    static int lastrefresh = 0;
    if(lastrefresh==shared::network::ftsClient.totalMilliseconds) return;
    if(shared::network::ftsClient.totalMilliseconds - lastrefresh > 1000)
    {
        loopv(servers) servers[i]->Reset();
        lastreset = shared::network::ftsClient.totalMilliseconds;
    }
    lastrefresh = shared::network::ftsClient.totalMilliseconds;

    checkresolver();
    checkpings();
    if(shared::network::ftsClient.totalMilliseconds - lastinfo >= servpingrate/(maxservpings ? max(1, (servers.length() + maxservpings - 1) / maxservpings) : 1)) pingservers();
    if(autosortservers) sortservers();
}

SCRIPTEXPORT void numservers()
{
    intret(servers.length());
}

#define GETSERVERINFO_(idx, si, body) \
    if(servers.inrange(idx)) \
    { \
        ServerInfo &si = *servers[idx]; \
        body; \
    }
#define GETSERVERINFO(idx, si, body) GETSERVERINFO_(idx, si, if(si.Valid()) { body; })

SCRIPTEXPORT void servinfovalid(int *i)
{
    GETSERVERINFO_(*i, si, intret(si.Valid() ? 1 : 0));
}

SCRIPTEXPORT void servinfodesc(int *i)
{
    GETSERVERINFO_(*i, si,
    {
        const char *status = si.Status();
        result(status ? status : si.desc);
    });
}

SCRIPTEXPORT void servinfoname(int *i)
{
    GETSERVERINFO_(*i, si, result(si.name));
}

SCRIPTEXPORT void servinfoport(int *i)
{
    GETSERVERINFO_(*i, si, intret(si.address.port));
}

SCRIPTEXPORT void servinfohaspassword(int *i)
{
    GETSERVERINFO_(*i, si, intret(si.password && si.password[0] ? 1 : 0));
}

SCRIPTEXPORT void servinfokeep(int *i)
{
    GETSERVERINFO_(*i, si, intret(si.keep ? 1 : 0));
}

SCRIPTEXPORT void servinfomap(int *i)
{
    GETSERVERINFO(*i, si, result(si.map));
}

SCRIPTEXPORT void servinfoping(int *i)
{
    GETSERVERINFO(*i, si, intret(si.ping));
}

SCRIPTEXPORT void servinfonumplayers(int *i)
{
    GETSERVERINFO(*i, si, intret(si.numberOfPlayers));
}

SCRIPTEXPORT void servinfomaxplayers(int *i)
{
    GETSERVERINFO(*i, si, intret(si.maximumOfPlayers));
}

SCRIPTEXPORT void servinfoplayers(int *i)
{
    GETSERVERINFO(*i, si,
    {
        if(si.maximumOfPlayers <= 0) intret(si.numberOfPlayers);
        else result(tempformatcubestr(si.numberOfPlayers >= si.maximumOfPlayers ? "\f3%d/%d" : "%d/%d", si.numberOfPlayers, si.maximumOfPlayers));
    });
}

SCRIPTEXPORT void servinfoattr(int *i, int *n)
{
    GETSERVERINFO(*i, si, { if(si.attr.inrange(*n)) intret(si.attr[*n]); });
}

SCRIPTEXPORT void connectservinfo(int *i, char *pw)
{
    GETSERVERINFO_(*i, si, engine::client::ConnectToServer(si.name, si.address.port, pw[0] ? pw : si.password));
}

game::server::ServInfo *getservinfo(int i)
{
    return servers.inrange(i) && servers[i]->Valid() ? servers[i] : NULL;
}

void clearservers(bool full = false)
{
    resolverclear();
    if(full) servers.deletecontents();
    else loopvrev(servers) if(!servers[i]->keep) delete servers.remove(i);
}

#define RETRIEVELIMIT 20000

void retrieveservers(vector<char> &data)
{
    ENetSocket sock = engine::client::ConnectMaster(true);
    if(sock == ENET_SOCKET_NULL) return;

    extern char *mastername;
    defformatcubestr(text, "retrieving servers from %s... (esc to abort)", mastername);
    renderprogress(0, text);

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
        renderprogress(min(float(timeout)/RETRIEVELIMIT, 1.0f), text);
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
        renderprogress(min(float(timeout)/RETRIEVELIMIT, 1.0f), text);
        if(interceptkey(SDLK_ESCAPE)) timeout = RETRIEVELIMIT + 1;
        if(timeout > RETRIEVELIMIT) break;
    }

    if(data.length()) data.add('\0');
    enet_socket_destroy(sock);
}

bool updatedservers = false;

SCRIPTEXPORT void updatefrommaster()
{
    vector<char> data;
    retrieveservers(data);
    if(data.empty()) conoutf("master server not replying");
    else
    {
        clearservers();
        execute(data.getbuf());
    }
    refreshservers();
    updatedservers = true;
}

SCRIPTEXPORT void initservers()
{
    if(autoupdateservers && !updatedservers) updatefrommaster();
}

SCRIPTEXPORT_AS(addserver) void addserver_scriptimpl(const char *name, int *port, const char *password)
{
    addserver(name, *port, password[0] ? password : NULL);
}

SCRIPTEXPORT void keepserver(const char *name, int *port, const char *password)
{
    addserver(name, *port, password[0] ? password : NULL, true);
}

SCRIPTEXPORT_AS(clearservers) void clearservers_scriptimpl(int *full)
{
    clearservers(*full!=0);
}

void writeservercfg()
{
    if(!game::savedservers()) return;
    stream *f = openutf8file(path(game::savedservers(), true), "w");
    if(!f) return;
    int kept = 0;
    loopv(servers)
    {
        ServerInfo *s = servers[i];
        if(s->keep)
        {
            if(!kept) f->printf("// servers that should never be cleared from the server list\n\n");
            if(s->password) f->printf("keepserver %s %d %s\n", escapeid(s->name), s->address.port, escapecubestr(s->password));
            else f->printf("keepserver %s %d\n", escapeid(s->name), s->address.port);
            kept++;
        }
    }
    if(kept) f->printf("\n");
    f->printf("// servers connected to are added here automatically\n\n");
    loopv(servers)
    {
        ServerInfo *s = servers[i];
        if(!s->keep)
        {
            if(s->password) f->printf("addserver %s %d %s\n", escapeid(s->name), s->address.port, escapecubestr(s->password));
            else f->printf("addserver %s %d\n", escapeid(s->name), s->address.port);
        }
    }
    delete f;
}


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
#if 0
#include "/Users/micha/dev/ScMaMike/src/build/binding/..+engine+serverbrowser.binding.cpp"
#endif
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
