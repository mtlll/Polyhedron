#include "baseentity.h"

namespace entities {
namespace classes {

void BaseEntity::preload() {}
void BaseEntity::think() {}
void BaseEntity::render() {}


//
// OnEvent callbacks.
//
bool BaseEntity::onTrigger(const entities::classes::CoreEntity *otherEnt, const vec &dir) { return false; }
bool BaseEntity::onTouch(const entities::classes::CoreEntity *otherEnt, const vec &dir) { return false; }
bool BaseEntity::onUse(CoreEntity *otherEnt, const vec &dir) { return false; }


void BaseEntity::on(const Event& event)
{
}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(BaseEntity, "base_entity", CoreEntity);
