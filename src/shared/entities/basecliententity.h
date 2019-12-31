#pragma once

#include "shared/entities/animinfo.h"
#include "shared/entities/basedynamicentity.h"
#include "shared/networking/cl_sv.h"
#include "shared/networking/protocol.h"

struct occludequery;
struct ragdolldata;

namespace entities
{
    namespace classes {

        //
        // A BaseClientEntity is an entity once derived from allows for it to take in userinput.
        // These are used for the Player, fake "clients" who join as (Player, whether they are disguised as monster or not.)
        // 
        // In either other case one is best off using BaseDynamicEntity, which serves its purpose as the use for general
        // entities.
        //
        class BaseClientEntity : public BaseDynamicEntity {
            ENTITY_FACTORY_IMPL(BaseClientEntity)
        public:
            virtual void stopmoving();
            virtual vec abovehead();

            //
            // Client variables.
            //
            DONTSERIALIZE shared::network::ClientInfo clientInformation;
        
            //
			// Entity member variables.
			//
            // WatIsDeze: Mike: These are there for the actual client entities. (Those who are bots, and real players on our screen.)
            DONTSERIALIZE bool k_left = false;
            DONTSERIALIZE bool k_right = false;
            DONTSERIALIZE bool k_up = false;
            DONTSERIALIZE bool k_down = false;   
            // WatIsDeze: Mike: These are already declared in BaseDynamicEntity and should thus have no need here anymore.
            // DONTSERIALIZE animinterpinfo animinterp[MAXANIMPARTS] { 0 };
            // DONTSERIALIZE ragdolldata *ragdoll = nullptr;
            // DONTSERIALIZE occludequery *query = nullptr;
            // DONTSERIALIZE int lastrendered = -1;
		protected:
        };
    } // classes
} // entities
