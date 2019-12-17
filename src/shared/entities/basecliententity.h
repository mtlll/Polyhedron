#pragma once

#include "cube.h"
#include "ents.h"

#include "shared/networking/network.h"
#include "shared/networking/protocol.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/cl_sv.h"

#include "shared/entities/animinfo.h"
#include "shared/entities/coreentity.h"
#include "shared/entities/baseentity.h"
#include "shared/entities/basephysicalentity.h"
#include "shared/entities/basedynamicentity.h"
#include "shared/entities/basecliententity.h"

struct occludequery;
struct ragdolldata;

namespace entities
{
    namespace classes {

        class BaseClientEntity : public BaseDynamicEntity
        {
            ENTITY_FACTORY_IMPL(BaseClientEntity)
        public:

            // Client Information.
            DONTSERIALIZE game::networking::ServerClientInfo ci;
		protected:
        };
    } // classes
} // entities
