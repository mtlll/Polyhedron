#pragma once
#include "animinfo.h"
#include "basephysicalentity.h"

struct occludequery;
struct ragdolldata;

namespace entities
{
    namespace classes {

        class BaseDynamicEntity : public BasePhysicalEntity
        {
            ENTITY_FACTORY_IMPL(BaseDynamicEntity)
        public:

            // Stop this entity from moving.
            virtual void stopmoving();

            // Returns the abovehead vector.
            vec abovehead();

            // WatIsDeze: Mike: I've commented these out, so that it actually takes a client entity to respond to "key up, down, left, right".
            // This is what separates entities based on Dynamic or Client, the other can't, and the other CAN take user input.
            DONTSERIALIZE animinterpinfo animinterp[MAXANIMPARTS] { 0 };
            DONTSERIALIZE ragdolldata *ragdoll = nullptr;
            DONTSERIALIZE occludequery *query = nullptr;
            DONTSERIALIZE int lastrendered = -1;

            // Allow for this entity to have a camera member, which can be used to follow the entity. (Imagine cutscenes, or multiplayer modes)
            DONTSERIALIZE entities::classes::BasePhysicalEntity *camera;
		protected:
        };
    } // classes
} // entities
