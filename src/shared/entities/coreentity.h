#pragma once

#include "cube.h"
#include "ents.h"
#include "entityfactory.h"
#include "engine/scriptexport.h"
#include <nlohmann/json.hpp>
#include <map>

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


	enum class EntityEventType
	{
		None,
		Tick,
		AttributeChanged,
		SelectStart,
		SelectStop,
		MoveStart,
		MoveStop,
		HoverStart,
		HoverStop,
		TouchStart,
		TouchStop,
		Use,
		Trigger,
		Precache,
		Spawn,
		ClearSpawn,
		
		Count
	};
	
	static const std::map<EntityEventType, std::string> EntityEventTypeToStringMap = {
		{EntityEventType::None, "None"},
		{EntityEventType::Tick, "Tick"},
		{EntityEventType::AttributeChanged, "AttributeChanged"},
		{EntityEventType::SelectStart, "SelectStart"},
		{EntityEventType::SelectStop, "SelectStop"},
		{EntityEventType::MoveStart, "MoveStart"},
		{EntityEventType::MoveStop, "MoveStop"},
		{EntityEventType::HoverStart, "HoverStart"},
		{EntityEventType::HoverStop, "HoverStop"},
		{EntityEventType::TouchStart, "TouchStart"},
		{EntityEventType::TouchStop, "TouchStop"},
		{EntityEventType::Use, "Use"},
		{EntityEventType::Trigger, "Trigger"},
		{EntityEventType::Precache, "Precache"},
		{EntityEventType::Spawn, "Spawn"},
		{EntityEventType::ClearSpawn, "ClearSpawn"},
		{EntityEventType::Count, "Count"}
	};
	
	struct Event
	{
		Event(EntityEventType type)
			: type(type)
		{}
		const EntityEventType type = EntityEventType::None;
	};

	template <EntityEventType E>
	struct EntityEvent : public Event
	{
		EntityEvent()
			: Event(E)
		{}
	};
	
	template <EntityEventType E, typename T>
	struct EntityEventData : public EntityEvent<E>
	{
		EntityEventData(const T& payload)
			: EntityEvent<E>()
			, payload(payload)
		{}
		
		const T payload;
	};
	
	struct EntityEventAttributeChanged : public EntityEventData<EntityEventType::AttributeChanged, std::string>
	{
		EntityEventAttributeChanged(const std::string& key)
			: EntityEventData<EntityEventType::AttributeChanged, std::string>(key)
		{}
	};
	
	struct EntityEventSelectStart : public EntityEvent<EntityEventType::SelectStart>
	{
	};

	struct EntityEventSelectStop : public EntityEvent<EntityEventType::SelectStop>
	{
	};

	struct EntityEventMoveStart : public EntityEvent<EntityEventType::MoveStart>
	{
	};

	struct EntityEventMoveStop : public EntityEvent<EntityEventType::MoveStop>
	{
	};

	struct EntityEventTouchStart : public EntityEvent<EntityEventType::TouchStart>
	{
	};

	struct EntityEventTouchStop : public EntityEvent<EntityEventType::TouchStop>
	{
	};

	struct EntityEventHoverStart : public EntityEventData<EntityEventType::HoverStart, int>
	{
		EntityEventHoverStart(int orient)
			: EntityEventData<EntityEventType::HoverStart, int>(orient)
		{}
	};

	struct EntityEventHoverStop : public EntityEvent<EntityEventType::HoverStop>
	{
	};

	struct EntityEventPrecache : public EntityEvent<EntityEventType::Precache>
	{
	};

	struct EntityEventSpawn : public EntityEvent<EntityEventType::Spawn>
	{
	};

	struct EntityEventClearSpawn : public EntityEvent<EntityEventType::ClearSpawn>
	{
	};

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
            DONTSERIALIZE uchar et_type = ET_GAMESPECIFIC;       // These are for the ET(Engine Type) values.
            DONTSERIALIZE uchar ent_type = ENT_INANIMATE; // These are for ENT_(DynEnt/PhysEnt Type) values.
            DONTSERIALIZE uchar game_type = GAMEENTITY;   // the internal game entity type values.
            uchar reserved = 0;
            short model_idx = -1;
            DONTSERIALIZE bool selected = false;
            DONTSERIALIZE bool hovered = false;
            DONTSERIALIZE bool moving = false;
            DONTSERIALIZE bool spawned = false;
			int flags = 0;
            DONTSERIALIZE int hover_orientation = 1;
            DONTSERIALIZE float hover_thickness = 3.f;

            CoreEntity *attached = nullptr;
			
            virtual bool getBoundingBox(int entselradius, vec &minbb, vec &maxbb) const;
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
    
	void send_entity_event(classes::CoreEntity* entity, const Event& event);
	void send_entity_event(int entity_id, const Event& event);

} // entities

//void coreentity_attributes();
