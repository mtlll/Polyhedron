#include "basedynamicentity.h"

namespace {
	float aboveeye = 1.0f;
}

namespace entities {
namespace classes {


// Stop movement.
void BaseDynamicEntity::stopmoving()
{
    k_left = k_right = k_up = k_down = jumping = false;
    move = strafe = crouching = 0;
}


vec BaseDynamicEntity::abovehead() {
    // WatIsDeze: Seems to determine to which lengths the camera and the character are allowed to go when jumping or crouching through a tunnel etc.
    return vec(o).addz(aboveeye+4);
}


void BaseDynamicEntity::on(const Event& event)
{
}

void BaseDynamicEntity::render(game::RenderPass pass)
{
}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(BaseDynamicEntity, "base_dynamic_entity", BasePhysicalEntity);
