#pragma once
#include "coreentity.h"

// Defined here, for several reasons, since it has to replace good ol' extentity.
namespace entities
{
    namespace classes
    {

        class DecalEntity : public CoreEntity
        {
            ENTITY_FACTORY_IMPL(DecalEntity);
        public:

            virtual bool getBoundingBox(int entselradius, ivec &minbb, ivec &maxbb) const;
        };
    } // classes
} // entities

