#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "cube.h"
#include "world.h"
#include "help.h"
#include "scriptexport.h"

#ifndef STANDALONE

#include "octa.h"
#include "light.h"
#include "texture.h"
#include "bih.h"
#include "model.h"
#include "ents.h"

extern entities::classes::Player *player;
extern entities::classes::BasePhysicalEntity *camera1;                // special ent that acts as camera, same object as player in FPS mode

extern int worldscale, worldsize;
extern int mapversion;
extern char *maptitle;
extern vector<ushort> texmru;
extern int xtraverts, xtravertsva;
extern const ivec cubecoords[8];
extern const ivec facecoords[6][4];
extern const uchar fv[6][4];
extern const uchar fvmasks[64];
extern const uchar faceedgesidx[6][4];
extern bool inbetweenframes, renderedframe;

extern SDL_Window *screen;
extern int screenw, screenh, renderw, renderh, hudw, hudh;

extern vector<int> entgroup;

//#include "pvs.h"
//#include "engine/font.h"
//#include "rendergl.h"

//config values from renderlights.h
#define LIGHTTILE_MAXW 16
#define LIGHTTILE_MAXH 16

//#include "renderva.h"
//#include "material.h"
//#include "water.h"
//#include "server.h"
//#include "serverbrowser.h"
//#include "client.h"
//#include "command.h"
//#include "console.h"
//#include "physics.h"
//#include "rendermodel.h"
//#include "renderparticles.h"
//#include "stain.h"
//#include "rendersky.h"
//#include "ui.h"
//#include "menus.h"
//#include "sound.h"
//#include "grass.h"
//#include "blend.h"
//#include "movie.h"
//#include "SoundConfig.h"

//TODO: Not sure what this is here for or where it's even implemented. Remove it?
void render3dbox(vec &o, float tofloor, float toceil, float xradius, float yradius = 0);

// main
enum
{
    NOT_INITING = 0,
    INIT_GAME,
    INIT_LOAD,
    INIT_RESET
};
extern int initing, numcpus;

enum
{
    CHANGE_GFX     = 1<<0,
    CHANGE_SOUND   = 1<<1,
    CHANGE_SHADERS = 1<<2
};
bool initwarning(const char *desc, int level = INIT_RESET, int type = CHANGE_GFX);

extern bool grabinput;

void pushevent(const SDL_Event &e);
bool interceptkey(int sym);

extern float loadprogress;
void renderbackground(const char *caption = NULL, Texture *mapshot = NULL, const char *mapname = NULL, const char *mapinfo = NULL, bool force = false);
void renderprogress(float bar, const char *text, bool background = false);

void getframemillis(float &avg, float &best, float &worst);
void getfps(int &fps, int &bestdiff, int &worstdiff);
void swapbuffers(bool overlay = true);
int getclockmillis();

enum { KR_CONSOLE = 1<<0, KR_GUI = 1<<1, KR_EDITMODE = 1<<2 };

void keyrepeat(bool on, int mask = ~0);

enum { TI_CONSOLE = 1<<0, TI_GUI = 1<<1 };

void textinput(bool on, int mask = ~0);

#endif
#endif