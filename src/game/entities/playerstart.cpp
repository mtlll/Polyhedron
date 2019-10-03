#include "../game.h"
#include "playerstart.h"

namespace entities {
namespace classes {

PlayerStart::PlayerStart() : BaseEntity() {
	// Reset defaults.
	reset();

	// Setup specifics.
	et_type = ET_GAMESPECIFIC;
    ent_type = ENT_INANIMATE;
	game_type = GAMEENTITY;
}

PlayerStart::~PlayerStart() {

}

void PlayerStart::preload() {

}

void PlayerStart::think() {

}

void PlayerStart::render() {

}

void PlayerStart::reset() {
	// Reset Base.
    BaseEntity::reset();

	// Set names.
	setName("PlayerStart");
	setClassName("playerstart");
}

} // classes
} // entities
