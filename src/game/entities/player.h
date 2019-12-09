#pragma once

#include "shared/networking/cl_sv.h"
#include "shared/entities/basecliententity.h"

struct vec;

namespace entities {
    namespace classes {
        class Player : public BaseClientEntity {
            ENTITY_FACTORY_IMPL(Player)
        public:
			//
			// Constructors/Destructor.
			//
            Player();

			//
			// Base/Core entity functions.
			//
            void preload();
            void think();
            void render();

			//
			// Entity functions.
			//
            void reset();
            void respawn();

			//
			// onEvent functions.
			//
            bool onTrigger(const entities::classes::CoreEntity *otherEnt, const vec &dir);
            bool onTouch(const entities::classes::CoreEntity *otherEnt, const vec &dir);

			//
			// Entity member variables.
			//
            DONTSERIALIZE entities::classes::BasePhysicalEntity *camera;

        private:

        };
    } // classes
} // entities

