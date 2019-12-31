#pragma once

#include "cube.h"
#include "ents.h"

namespace entities
{
	namespace classes
	{
		class Player;
		class BaseEntity;
        class BaseClientEntity;
	}
}

namespace game
{
    // Extern variables.
    extern entities::classes::Player *clPlayer;         // Main player entity in the game code/
	extern vector<::entities::classes::Player *> clPlayers;    // List of connected players. (For future network usage.)
    extern int maptime, maprealtime;                    // Times.
    extern cubestr clientmap;                           // The map the client is currently running or loading.

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

    extern void saveragdoll(entities::classes::CoreEntity *d);
    extern void clearragdolls();
    extern void moveragdolls();
    extern const playermodelinfo &getplayermodelinfo(entities::classes::CoreEntity *d);
    extern int getplayercolor(entities::classes::CoreEntity *d, int team);
    extern int chooserandomplayermodel(int seed);
    extern void syncplayer();
    extern void swayhudgun(int curtime);
    extern vec hudgunorigin(int gun, const vec &from, const vec &to, entities::classes::CoreEntity *d);

    // Did we need all these too? It is getting confusing. We'll see what it ends up into.
    extern void parseoptions(vector<const char *> &args);

    extern void gamedisconnect(bool cleanup);
    extern void parsepacketclient(int chan, packetbuf &p);
    extern void connectattempt(const char *name, const char *password, const ENetAddress &address);
    extern void connectfail();
    extern void gameconnect(bool _remote);
    extern bool allowedittoggle();
    extern void edittoggled(bool on);
    extern void writeclientinfo(stream *f);
    extern void toserver(char *text);
    extern void changemap(const char *name);
    extern void forceedit(const char *name);
    extern bool allowmouselook();

    extern const char *gameident();
    extern const char *gameconfig();
    extern const char *savedconfig();
    extern const char *restoreconfig();
    extern const char *defaultconfig();
    extern const char *autoexec();
    extern const char *savedservers();
    extern void loadconfigs();

    extern void UpdateWorld();
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
};