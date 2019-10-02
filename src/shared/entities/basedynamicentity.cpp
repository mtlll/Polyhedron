#include "cube.h"
#include "ents.h"
#include "game.h"
#include "basephysicalentity.h"
#include "basedynamicentity.h"

namespace entities {
namespace classes {


// WatIsDeze: TODO: Maybe remove the physent constructor from here.
BaseDynamicEntity::BaseDynamicEntity() : BasePhysicalEntity(), ragdoll(NULL), query(NULL), lastrendered(0)
{
    reset();
    setName("basedynamicentity");
    setClassName("BaseDynamicEntity");
}

BaseDynamicEntity::~BaseDynamicEntity()
{
    #ifndef STANDALONE
        //extern void cleanragdoll(BaseDynamicEntity *d);
        //if(ragdoll) cleanragdoll(this);
    #endif
}

// Stop movement.
void BaseDynamicEntity::stopmoving()
{
    k_left = k_right = k_up = k_down = jumping = false;
    move = strafe = crouching = 0;
}

// Reset to basic state values.
void BaseDynamicEntity::reset() {
    // Reset base physical values.
    BasePhysicalEntity::reset();

    // Stop moving.
    stopmoving();

    // Reset all animations.
    loopi(MAXANIMPARTS) animinterp[i].reset();
}

vec BaseDynamicEntity::abovehead() {
    // WatIsDeze: Seems to determine to which lengths the camera and the character are allowed to go when jumping or crouching through a tunnel etc.
    return vec(o).addz(aboveeye+4);
}

} // classes
} // entities
