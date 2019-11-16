#pragma once
#include "shared/entities/basedynamicentity.h"
#include "engine/engine.h"

namespace entities
{
    namespace classes
    {
        class BaseMapModel : public BaseDynamicEntity {
			ENTITY_FACTORY_IMPL(BaseMapModel);
        public:
            BaseMapModel();
            BaseMapModel(const std::string &filename);

            virtual void preload();
            virtual void think();
            virtual void render();

            virtual void onAnimate(int &anim, int &basetime);

            virtual bool getBoundingBox(int entselradius, ivec &minbb, ivec &maxbb) const;
        public:
            void preloadMapModel(const std::string &filename);

        private:
            void loadModelAttributes();

        private:
            DONTSERIALIZE mapmodelinfo mmi;
            PHUI_INPUT("Model") std::string modelname;
        };
		
    } // classes
} // entities
