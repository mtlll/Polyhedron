#pragma once

#include "cube.h"
#include "ents.h"
#include "entityfactory.h"
#include "engine/scriptexport.h"
#include <nlohmann/json.hpp>

namespace json_utils
{
	const nlohmann::json getSubobject(const nlohmann::json& document, const std::string& key);
}

namespace entities {
	enum class EntityEditorState : int
	{
		Selected = 		1 << 1,
		Hover = 		1 << 2,
		Dragging = 		1 << 3
	};
	
	inline int operator~ (EntityEditorState a) { return ~(int)a; }
	inline int operator| (EntityEditorState a, EntityEditorState b) { return ((int)a | (int)b); }
	inline int operator& (EntityEditorState a, EntityEditorState b) { return ((int)a & (int)b); }
	inline int operator^ (EntityEditorState a, EntityEditorState b) { return ((int)a ^ (int)b); }
	inline int& operator|= (EntityEditorState& a, EntityEditorState b) { return ((int&)a |= (int)b); }
	inline int& operator&= (EntityEditorState& a, EntityEditorState b) { return ((int&)a &= (int)b); }
	inline int& operator^= (EntityEditorState& a, EntityEditorState b) { return ((int&)a ^= (int)b); }

    namespace classes {

        class CoreEntity
        {
            ENTITY_FACTORY_IMPL(CoreEntity)
        public:

			void saveToJson(nlohmann::json& document);
			void loadFromJson(const nlohmann::json& document);

            vec o {0.0f, 0.0f, 0.0f};       // position
            PHUI_SLIDER("Attribute 1", -180, 180, 1) int attr1 = 0;
            PHUI_CHECKBOX("Attribute 2") int attr2 = 0;
            int attr3 = 0;
            int attr4 = 0;
            int attr5 = 0;
            DONTSERIALIZE uchar et_type = ET_EMPTY;       // These are for the ET(Engine Type) values.
            DONTSERIALIZE uchar ent_type = ENT_INANIMATE; // These are for ENT_(DynEnt/PhysEnt Type) values.
            DONTSERIALIZE uchar game_type = GAMEENTITY;   // the internal game entity type values.
            uchar reserved = 0;
            short model_idx = 0;
            DONTSERIALIZE bool selected = false;

            int flags = EntityFlags::EF_NOFLAG;
            CoreEntity *attached = nullptr;

            bool spawned() const;
            void setspawned(bool val);
            void setspawned();
            void clearspawned();
            
            virtual void onSelected(bool selected);
                        
            virtual bool getBoundingBox(int entselradius, ivec &minbb, ivec &maxbb) const;
            virtual void renderForEdit();
            virtual void renderForEditGui();
            virtual void renderSelected(int entselradius, int entorient);
			void renderHighlight(int entselradius, int entorient, float thickness);
			void renderMoveShadow(int entselradius, int size);
        public:

            PHUI_INPUT("Name (for triggers)") std::string name = "coreentity_unnamed";
        };
        
        
		void from_json(const nlohmann::json& document,  entities::classes::CoreEntity* entity_ptr);
		void to_json(nlohmann::json& document, const entities::classes::CoreEntity* entity_ptr);
        
		void from_json(const nlohmann::json& document,  entities::classes::CoreEntity& entity_t);
		void to_json(nlohmann::json& document, const entities::classes::CoreEntity& entity_t);
    } // classes
} // entities

//void coreentity_attributes();
