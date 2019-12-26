#include "basemonster.h"

namespace entities {
namespace classes {

BaseMonster::BaseMonster() {
    ent_type = ENT_AI;
}

void BaseMonster::preload() {
    conoutf("%s", "Preloading basemonster entity");
}

void BaseMonster::think() {
    //moveplayer(this, 10, true);
}z

void BaseMonster::render() {
    // TODO: Fix this.
    //if(isthirdperson()) renderclient(clPlayer, "ogro", NULL, 0, ANIM_ATTACK1, 300, clPlayer->lastaction, clPlayer->lastpain);
}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(BaseMonster, "base_monster", BaseEntity);
