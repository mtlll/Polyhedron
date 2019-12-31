#include "cube.h"
#include "game/game.h"
#include "game/entities/player.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/protocol.h"

#include "shared/entities/coreentity.h"
#include "shared/entities/baseentity.h"
#include "shared/entities/basedynamicentity.h"
#include "shared/entities/basecliententity.h"

namespace entities {
namespace classes {

BaseClientEntity::BaseClientEntity() : BaseDynamicEntity() {
	state = CS_ALIVE;
	et_type = ET_GAMESPECIFIC;
	ent_type = ENT_PLAYER;
	game_type = CLIENT_BASIC;
	collidetype = COLLIDE_OBB;
	physstate = PHYS_FALL;

	// Load in our player entity model.
	conoutf("%s", "Preloading base client  entity");
	preloadmodel("player/male");
	
	// This should NOT occure..
	clientInformation->nickname = "BaseClient";
}

void BaseClientEntity::SetNickName(const std::string &nick) {
	clientInformation.nickname = nick;
}

void BaseClientEntity::stopmoving()
{
	// First call its predesecsor.
	BaseDynamicEntity::stopmoving();

	// No keyboard directions. Turn them off.
	k_left = k_right = k_up = k_down = false;
}

vec BaseClientEntity::abovehead() {
	// First call its predesecsor.
	BaseDynamicEntity::abovehead();

	// WatIsDeze: Seems to determine to which lengths the camera and the character are allowed to go when jumping or crouching through a tunnel etc.
	return vec(o).addz(aboveeye+4);
}

}; // classes
}; // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(BaseClientEntity, "base_client_entity", BaseDynamicEntity);
