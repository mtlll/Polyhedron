#pragma once

#include "shared/command.h"
#include "engine/scriptexport.h"

namespace entities
{
    namespace classes
    {
        class Player;
        class BasePhysicalEntity;
    }
}

namespace game
{
    extern entities::classes::Player *player1;
    extern entities::classes::BasePhysicalEntity *camera1;
}

extern entities::classes::Player *player;

