#pragma once 

#include "cube.h"
#include "ents.h"

namespace entities {
    namespace classes {
		class Player;
		class BaseEntity;
        class BasePhysicalEntity;
        class BaseDynamicEntity;
        class BaseClientEntity;
        class BaseAIEntity;
        class Player;
	}
}

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/protocol.h"

namespace game {
    namespace networking {
        namespace protocol {

        };

        //
        // Console message types
        //
        enum
        {
            CON_CHAT       = 1<<8,
            CON_TEAMCHAT   = 1<<9,
            CON_GAMEINFO   = 1<<10,
            CON_FRAG_SELF  = 1<<11,
            CON_FRAG_OTHER = 1<<12,
            CON_TEAMKILL   = 1<<13
        };
    };

    // Extern variables.
    extern entities::classes::Player *player1;  // Main player entity in the game code.
    extern vector<entities::classes::BaseClientEntity *> players; // Players array. (Client side, it is clients on the server side.)

    extern networking::GameMode gameMode;     // Current game mode (M_LOBBY, M_EDIT | M_LOCAL etc)
    extern networking::protocol::MasterMode masterMode; // Master Privilige mode (when hosting with this client).

    extern int mapTime, mapRealTime;            // Times.
    extern cubestr clientMap;                   // The map the client is currently running or loading.

    extern bool sendItemsToServer, sendCRC; // after a map change, since server doesn't have map data
    extern int lastPing;

    extern bool connected, remote, demoPlayback, gamePaused;
    extern int sessionID, gameSpeed;

    extern cubestr servDesc, servAuth, connectPass;

    #define MAXTEAMS 2
    static const char * const teamnames[1+MAXTEAMS] = { "", "azul", "rojo" };
    static const char * const teamtextcode[1+MAXTEAMS] = { "\f0", "\f1", "\f3" };
    static const int teamtextcolor[1+MAXTEAMS] = { 0x1EC850, 0x6496FF, 0xFF4B19 };
    static const int teamscoreboardcolor[1+MAXTEAMS] = { 0, 0x3030C0, 0xC03030 };
    static const char * const teamblipcolor[1+MAXTEAMS] = { "_neutral", "_blue", "_red" };
    static inline int teamnumber(const char *name) { loopi(MAXTEAMS) if(!strcmp(teamnames[1+i], name)) return 1+i; return 0; }
    #define validteam(n) (static_cast<int>(n) >= 1 && static_cast<int>(n) <= MAXTEAMS)
    #define teamname(n) (teamnames[validteam(n) ? static_cast<int>(n) : 0])

    // network quantization scale
    #define DMF 8.0f                // for world locations
    #define DNF 100.0f              // for normalized vectors
    #define DVELF 1.0f              // for playerspeed based velocity vectors

    enum                            // static entity types
    {
        NOTUSED = ET_EMPTY,         // entity slot not in use in map
        LIGHT = ET_LIGHT,           // lightsource, attr1 = radius, attr2 = intensity
        MAPMODEL = ET_MAPMODEL,     // attr1 = idx, attr2 = yaw, attr3 = pitch, attr4 = roll, attr5 = scale
        PLAYERSTART,                // attr1 = angle, attr2 = team
        ENVMAP = ET_ENVMAP,         // attr1 = radius
        PARTICLES = ET_PARTICLES,
        MAPSOUND = ET_SOUND,
        SPOTLIGHT = ET_SPOTLIGHT,
        DECAL = ET_DECAL,
        TELEPORT,                   // attr1 = idx, attr2 = model, attr3 = tag
        TELEDEST,                   // attr1 = angle, attr2 = idx
        JUMPPAD,                    // attr1 = zpush, attr2 = ypush, attr3 = xpush
        FLAG,                       // attr1 = angle, attr2 = team
        GAMEENTITY,					// classname = game entity class type, attributes list is what it is, and can be accessed in any derived BaseEntity class.
        MAXENTTYPES,

        I_FIRST = 0,
        I_LAST = -1
    };

    enum { GUN_RAIL = 0, GUN_PULSE, NUMGUNS };
    enum { ACT_IDLE = 0, ACT_SHOOT, ACT_MELEE, NUMACTS };
    enum { ATK_RAIL_SHOOT = 0, ATK_RAIL_MELEE, ATK_PULSE_SHOOT, ATK_PULSE_MELEE, NUMATKS };

    #define validgun(n) ((n) >= 0 && (n) < NUMGUNS)
    #define validact(n) ((n) >= 0 && (n) < NUMACTS)
    #define validatk(n) ((n) >= 0 && (n) < NUMATKS)

    static struct GameModeInfo
    {
        const char *name, *prettyname;
        networking::GameMode flags;
        const char *info;
    } gameModes[] = {
        { "demo", "Demo", networking::GameMode::Demo | networking::GameMode::Local, NULL},
        { "edit", "Edit", networking::GameMode::Edit, "Cooperative Editing:\nEdit maps with multiple players simultaneously." },
        { "rdm", "rDM", networking::GameMode::Lobby | networking::GameMode::Rail, "Railgun Deathmatch:\nFrag everyone with railguns to score points." },
        { "pdm", "pDM", networking::GameMode::Lobby | networking::GameMode::Pulse, "Pulse Rifle Deathmatch:\nFrag everyone with pulse rifles to score points." },
        { "rtdm", "rTDM", networking::GameMode::Team | networking::GameMode::Rail, "Railgun Team Deathmatch:\nFrag \fs\f3the enemy team\fr with railguns to score points for \fs\f1your team\fr." },
        { "ptdm", "pTDM", networking::GameMode::Team | networking::GameMode::Pulse, "Pulse Rifle Team Deathmatch:\nFrag \fs\f3the enemy team\fr with pulse rifles to score points for \fs\f1your team\fr." },
        { "rctf", "rCTF", networking::GameMode::Ctf | networking::GameMode::Team | networking::GameMode::Rail, "Railgun Capture The Flag:\nCapture \fs\f3the enemy flag\fr and bring it back to \fs\f1your flag\fr to score points for \fs\f1your team\fr." },
        { "pctf", "pCTF", networking::GameMode::Ctf | networking::GameMode::Team | networking::GameMode::Pulse, "Pulse Rifle Capture The Flag:\nCapture \fs\f3the enemy flag\fr and bring it back to \fs\f1your flag\fr to score points for \fs\f1your team\fr." },
    };

    #define STARTGAMEMODE (-1)
    #define NUMGAMEMODES ((int)(sizeof(game::gameModes)/sizeof(game::gameModes[0])))

    #define m_valid(mode)          (static_cast<int>(mode) >= STARTGAMEMODE && static_cast<int>(mode) < STARTGAMEMODE + NUMGAMEMODES)
    #define m_check(mode, flag)    (static_cast<int>(m_valid(static_cast<int>(mode)) && static_cast<int>(game::gameModes[static_cast<int>(mode) - STARTGAMEMODE].flags&(flag))))
    #define m_checknot(mode, flag) (static_cast<int>(m_valid(static_cast<int>(mode)) && !(static_cast<int>(game::gameModes[static_cast<int>(mode) - STARTGAMEMODE].flags&(flag)))))
    #define m_checkall(mode, flag) (static_cast<int>(m_valid(static_cast<int>(mode)) && (static_cast<int>(game::gameModes[static_cast<int>(mode) - STARTGAMEMODE].flags&(flag)) == (flag))))

    #define m_ctf          (static_cast<int>(m_check(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::Ctf))))
    #define m_teammode     (static_cast<int>(m_check(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::Team))))
    #define m_overtime     (static_cast<int>(m_check(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::OverTime))))
    #define isteam(a,b)    (static_cast<int>(m_teammode) && static_cast<int>(a)==static_cast<int>(b))
    #define m_rail         (m_check(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::Rail)))
    #define m_pulse        (m_check(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::Pulse)))

    #define m_demo         (m_check(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::Demo))))
    #define m_edit         (m_check(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::Edit))))
    #define m_lobby        (m_check(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::Lobby))))
    #define m_timed        (m_checknot(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::Demo)|static_cast<int>(networking::GameMode::Edit) | static_cast<int>(networking::GameMode::Edit(networking::GameMode::Local)))))
    #define m_botmode      (m_checknot(static_cast<int>(game::gameMode), static_cast<int>(game::networking::GameMode::Demo)|static_cast<int>(networking::GameMode::Local))))
    #define m_mp(mode)     (m_checknot(static_cast<int>(mode), static_cast<int>(game::networking::GameMode::Local))))




    //
    // Configs and Init/Deinit
    //
    extern void InitClient();
    extern const char *GameIdent();
    extern const char *GameCfg();
    extern const char *SavedCfg();
    extern const char *DefaultCfg();
    extern const char *AutoExecCfg();
    extern const char *SavedServersCfg();
    extern void LoadCfgs();

    // Entities.
    extern void clearworld();

    // Update functions.
    extern void updateentities();

    // Render functions.
    extern void rendergame(bool mainpass);
    extern void renderobjects();

    // HUD functions.
    extern float clipconsole(float w, float h);

    // Physics.
    extern void physicstrigger(entities::classes::BasePhysicalEntity *d, bool local, int floorlevel, int waterlevel, int material);

    // Renderer.
    #define MAXTEAMS 2
    struct playermodelinfo
    {
        const char *model[1+MAXTEAMS], *hudguns[1+MAXTEAMS],
                   *icon[1+MAXTEAMS];
        bool ragdoll;
    };

    extern void saveragdoll(entities::classes::BaseClientEntity *d);
    extern void clearragdolls();
    extern void moveragdolls();
    extern const playermodelinfo &getplayermodelinfo(entities::classes::BaseClientEntity *d);
    extern int getplayercolor(entities::classes::BaseClientEntity *d, int team);
    extern int chooserandomplayermodel(int seed);
    extern void syncplayer();
    extern void swayhudgun(int curtime);
    extern vec hudgunorigin(int gun, const vec &from, const vec &to, entities::classes::BaseClientEntity *d);


    extern bool clientoption(const char *arg);
    extern ::entities::classes::BaseClientEntity *GetClient(int cn);
    extern ::entities::classes::BaseClientEntity *NewClient(int cn);
    extern const char *GenerateClientColorName(::entities::classes::BaseClientEntity *d, const char *name = NULL, const char *alt = NULL, const char *color = "");
    extern const char *TeamColorName(::entities::classes::BaseClientEntity *d, const char *alt = "you");
    extern const char *TeamColor(const char *prefix, const char *suffix, int team, const char *alt = "Team");
    extern ::entities::classes::BaseClientEntity *PointAtPlayer();
    extern ::entities::classes::BaseClientEntity *HUDPlayer();
    extern ::entities::classes::BaseClientEntity *FollowingPlayer();
    extern void StopFollowing();
    extern void CheckFollow();
    extern void NextFollow(int dir = 1);
    extern void ClientDIsConnected(int cn, bool notify = true);
    extern void ClearClients(bool notify = true);
    extern void StartGame();
}

namespace server
{
    extern const char *modename(int n, const char *unknown = "unknown");
    extern const char *modeprettyname(int n, const char *unknown = "unknown");
    extern const char *mastermodename(int n, const char *unknown = "unknown");
    extern void startintermission();
    extern void stopdemo();
    extern void forcemap(const char *map, int mode);
    extern void forcepaused(bool paused);
    extern void forcegamespeed(int speed);
    extern void hashpassword(int cn, int sessionid, const char *pwd, char *result, int maxlen = MAXSTRLEN);
    extern int MessageSizeLookup(game::networking::protocol::NetClientMessage msg);
    extern bool serveroption(const char *arg);
    extern bool delayspawn(int type);
}