#pragma once
#include "shared/entities/basephysicalentity.h"

namespace entities {
    namespace classes {
        class DynamicLight : public BasePhysicalEntity {
			ENTITY_FACTORY_IMPL(DynamicLight);
        public:
            DynamicLight();

            void preload();
            void think();

            enum DYNAMIC_LIGHT_STATE {
                ON,
                OFF,
                FLICKERING,
                FADING
            };
//
//			NLOHMANN_JSON_SERIALIZE_ENUM( DYNAMIC_LIGHT_STATE, {
//				{ON, "ON"},
//				{OFF, "OFF"},
//				{FLICKERING, "FLICKERING"},
//				{FADING, "FADING"},
//			});

            void setState(DynamicLight::DYNAMIC_LIGHT_STATE &state);

        public:
            //
            // Light states.
            //
            // Stores the current state of the dynamic light.
            DynamicLight::DYNAMIC_LIGHT_STATE lightState;

            // Obviously speaks for itself, the color.
            vec4 lightColor;
			
        };
    } // classes
} // entities	
