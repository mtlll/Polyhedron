// the interface the engine uses to run the gameplay module

namespace entities
{
    // Predefined.
    namespace classes {
        class BaseEntity;
    }

    extern void editent(int i, bool local);
    extern const char *entnameinfo(entities::classes::CoreEntity *e);
    extern const char *entname(int i);
    extern float dropheight(entities::classes::CoreEntity *e);
    extern void fixentity(entities::classes::CoreEntity *e);
    extern void entradius(entities::classes::CoreEntity *e, bool color);
    extern bool mayattach(entities::classes::CoreEntity *e);
    extern bool attachent(entities::classes::CoreEntity *e, entities::classes::CoreEntity *a);
    extern bool printent(entities::classes::CoreEntity *e, char *buf, int len);
    extern entities::classes::CoreEntity *newgameentity(const char *strclass);
    extern void deletegameentity(entities::classes::CoreEntity *e);
    extern void clearents();
    extern vector<entities::classes::CoreEntity *> &getents();
    extern const char *entmodel(const entities::classes::CoreEntity *e);
    extern void animatemapmodel(const entities::classes::CoreEntity *e, int &anim, int &basetime);
}

namespace game
{
    extern void ParseOptions(vector<const char *> &args);

    extern void GameDisconnect(bool cleanup);
    extern void ParsePacketclient(int chan, packetbuf &p);
    extern void ConnectAttempt(const char *name, const char *password, const ENetAddress &address);
    extern void ConnectFail();
    extern void GameConnect(bool _remote);
    extern bool allowedittoggle();
    extern void edittoggled(bool on);
    extern void writeclientinfo(stream *f);
    extern void toserver(char *text);
    extern void changemap(const char *name);
    extern void forceedit(const char *name);
    extern bool ispaused();
    extern int scaletime(int t);
    extern bool allowmouselook();

    extern const char *GameIdent();
    extern const char *GameCfg();
    extern const char *SavedCfg();
    extern const char *DefaultCfg();
    extern const char *AutoExecCfg();
    extern const char *SavedServersCfg();
    extern void LoadCfgs();

    extern void updateworld();
    extern void InitClient();
    extern void physicstrigger(entities::classes::BasePhysicalEntity *d, bool local, int floorlevel, int waterlevel, int material = 0);
    extern void bounced(entities::classes::BasePhysicalEntity *d, const vec &surface);
    extern void edittrigger(const selinfo &sel, int op, int arg1 = 0, int arg2 = 0, int arg3 = 0, const VSlot *vs = NULL);
    extern void vartrigger(ident *id);
    extern void dynentcollide(entities::classes::BaseDynamicEntity *d, entities::classes::BaseDynamicEntity *o, const vec &dir);

    // WatIsDeze: TODO: Maybe remove.
    extern void mapmodelcollide(entities::classes::CoreEntity *d, entities::classes::CoreEntity *o, const vec &dir);
    extern const char *getclientmap();
    extern const char *getmapinfo();
    extern const char *getscreenshotinfo();
    extern void resetgamestate();
    extern void suicide(entities::classes::CoreEntity *d);
    extern void newmap(int size);
    extern void startmap(const char *name);
    extern void preload();
    extern float abovegameplayhud(int w, int h);
    extern void gameplayhud(int w, int h);
    extern bool canjump();
    extern bool cancrouch();
    extern bool allowmove(entities::classes::BasePhysicalEntity *d);
    extern entities::classes::CoreEntity *iterdynents(int i);
    extern int numdynents();
    extern void RenderGameEntities();
    extern void renderavatar();
    extern void renderplayerpreview(int model, int color, int team, int weap);
    extern int numanims();
    extern void findanims(const char *pattern, vector<int> &anims);
    extern void writegamedata(vector<char> &extras);
    extern void readgamedata(vector<char> &extras);
    extern float clipconsole(float w, float h);
    extern const char *defaultcrosshair(int index);
    extern int selectcrosshair(vec &col);
    extern void setupcamera();
    extern bool detachcamera();
    extern bool collidecamera();
    extern void renderDynamicLights();
    extern void particletrack(entities::classes::CoreEntity *owner, vec &o, vec &d);
    extern void dynlighttrack(entities::classes::CoreEntity *owner, vec &o, vec &hud);
    extern bool needminimap();

    namespace server
    {
        extern void *NewClientInfo();
        extern void DeleteClientInfo(void *ci);

        extern void ServerInit();
        extern int ReserveClients();
        extern int GetNumChannels();
        extern void ClientDisconnect(int n);
        extern int ClientConnect(int n, uint ip);
        extern void LocalDisconnect(int n);
        extern void LocalConnect(int n);
        extern bool AllowBroadcast(int n);
        extern void RecordPacket(int chan, void *data, int len);
        extern void ParsePacket(int sender, int chan, packetbuf &p);
        extern void SendServMsg(const char *s);
        extern bool SendPackets(bool force = false);
        extern void ServerInfoReply(ucharbuf &req, ucharbuf &p);
        extern void ServerUpdate();
        extern int ProtocolVersion();
        extern int LanInfoPort();
        extern int ServerPort();
        extern const char *DefaultMaster();
        extern int MasterPort();
        extern void ProcessMasterInput(const char *cmd, int cmdlen, const char *args);
        extern void MasterConnect();
        extern void MasterDisconnected();
        extern bool IsPaused();
        extern int ScaleTime(int t);
    };
};

