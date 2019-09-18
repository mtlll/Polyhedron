#include "../game.h"
#include "../engine/engine.h"
#include "basemapmodel.h"
#include "door.h"

namespace entities {
namespace classes {

Door::Door() : entities::classes::BaseMapModel("") {
    // Doors animate, makes sense.
    flags |= EF_ANIM;
}

Door::~Door() {

}

void Door::preload() {

}
void Door::think() {}
void Door::render() {}

bool Door::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {
    if (otherEnt == NULL) {
        return false;
    }
    conoutf("%s %s %s %f %f %f", "Door triggered by entity: ", otherEnt->classname.c_str(),
            "from Vector Direction: ", dir.x, dir.y, dir.z);
    return true;
}

bool Door::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {
    if (otherEnt == NULL) {
        return false;
    }
    conoutf("%s %s %s %f %f %f", "Door touched by entity: ", otherEnt->classname.c_str(),
            "from Vector Direction: ", dir.x, dir.y, dir.z);
    return true;
}

} // classes
} // entities
