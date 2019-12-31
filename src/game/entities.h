#pragma once 

namespace entities
{
    namespace classes {
        class CoreEntity;
        class BaseEntity;
        class BasePhysicalEntity;
        class BaseDynamicEntity;
        class BaseMapModel;
        class DynamicLight;
        class Player;
    }

    // Entity arrays.
    extern vector<classes::BaseEntity *> g_ents;
    extern vector<classes::BaseEntity *> g_lightEnts;

    //
    // Entity core functions.
    //
    // Preloads the entities.
    extern void preloadentities();

    // Renders all the entities.
   // extern void renderentities();

    // Sets the spawn state on a given entity index.
    extern void setspawn(int i, bool on);

    // Resets all the spawns.
    extern void resetspawns();

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