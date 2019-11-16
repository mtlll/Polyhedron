#include "engine.h"
#include "game.h"
#include "entities.h"

// Base entities.
#include "entities/basemonster.h"
#include "entities/basemapmodel.h"

// Game entities.
#include "entities/door.h"
#include "entities/dynamiclight.h"
#include "entities/playerstart.h"
#include "entities/player.h"
#include "shared/entities/entityfactory.h"

namespace entities
{
	using namespace game;

#ifndef STANDALONE

	vector<entities::classes::CoreEntity *> &getents() {
		static vector<entities::classes::CoreEntity *> g_ents;
		return g_ents;
	}

	bool mayattach(entities::classes::BasePhysicalEntity *e) { return false; }
	bool mayattach(entities::classes::CoreEntity *e) { return false; }
	bool attachent(entities::classes::CoreEntity *e, entities::classes::CoreEntity *a) { return false; }

	const char *itemname(int i)
	{
		return nullptr;
#if 0
		int t = ents[i]->type;
		if(!validitem(t)) return NULL;
		return itemstats[t-I_FIRST].name;
#endif
	}

	int itemicon(int i)
	{
		return -1;
#if 0
		int t = ents[i]->type;
		if(!validitem(t)) return -1;
		return itemstats[t-I_FIRST].icon;
#endif
	}

	const char *entmdlname(int type)
	{
		return "";
	}

	const char *entmodel(const entities::classes::CoreEntity *e)
	{
		return nullptr;
	}

	void preloadentities()
	{
		// Execute preload actions for entities.
		loopv(entities::getents())
		{
			if (getents().inrange(i) && getents()[i] != nullptr) {
				// Let's go at it!
				auto entity = entities::getents()[i];
				entities::send_entity_event(entity, entities::EntityEventPrecache());
			 }
		}

		// Specifically load in the client player model.
		if (game::player1 != nullptr) {
			entities::send_entity_event(game::player1, entities::EntityEventPrecache());
		}
	}

	void resetspawns() {
		loopv(entities::getents())
			if (entities::getents().inrange(i) && entities::getents()[i] != nullptr)
				entities::getents()[i]->clearspawned();

		if (game::player1 != nullptr)
			game::player1->clearspawned();
	}

	void setspawn(int i, bool on) { if(entities::getents().inrange(i) && entities::getents()[i] != nullptr) entities::getents()[i]->setspawned(on); }

	void deletegameentity(entities::classes::CoreEntity *e)
	{
		delete e;
	}

	// Deletes all game entities in the stack.
	void clearents()
	{
		// Delete stack entities.
		while(entities::getents().length()) deletegameentity(entities::getents().pop());
	}

	void animatemapmodel(const entities::classes::CoreEntity *e, int &anim, int &basetime)
	{/*        const fpsentity &f = (const fpsentity &)e;
		if(validtrigger(f.attr3)) switch(f.triggerstate)
		{
			case TRIGGER_RESET: anim = ANIM_TRIGGER|ANIM_START; break;
			case TRIGGERING: anim = ANIM_TRIGGER; basetime = f.lasttrigger; break;
			case TRIGGERED: anim = ANIM_TRIGGER|ANIM_END; break;
			case TRIGGER_RESETTING: anim = ANIM_TRIGGER|ANIM_REVERSE; basetime = f.lasttrigger; break;
		}*/
		//const entities::classes::BaseMapModelEntity *ent = (const entities::classes::BaseMapModelEntity&)e;
		//anim = ANIM_MAPMODEL | ANIM_START | ANIM_LOOP;
		//basetime = SDL_GetTicks() - e.reserved;
		//e.reserved = SDL_GetTicks();

	}

	void entradius(entities::classes::CoreEntity *e, bool color)
	{
/*		switch(e->game_type)
		{
			case TELEPORT:
				loopv(entities::getents()) if(entities::getents()[i]->game_type == TELEDEST && e->attr1==entities::getents()[i]->attr2)
				{
					renderentarrow(e, vec(entities::getents()[i]->o).sub(e->o).normalize(), e->o.dist(entities::getents()[i]->o));
					break;
				}
				break;

			case JUMPPAD:
				renderentarrow(e, vec((int)(char)e->attr3*10.0f, (int)(char)e->attr2*10.0f, e->attr1*12.5f).normalize(), 4);
				break;

			case FLAG:
			case TELEDEST:
			{
				vec dir;
				vecfromyawpitch(e->attr1, 0, 1, 0, dir);
				renderentarrow(e, dir, 4);
				break;
			}
		}*/
	}

	bool printent(entities::classes::CoreEntity *e, char *buf, int len)
	{
		return false;
	}

	const char *entname(int i)
	{
		auto& ents = getents();
		
		if (i >= 0 && i < ents.length())
		{
			entities::classes::CoreEntity *ent = ents[i];
			return ent->name.c_str();
		}

		return "";
	}

	void editent(int i, bool local)
	{
		extern int edit_entity;
		auto& ents = getents();

		if (edit_entity != i)
		{
			if (edit_entity >= 0 && edit_entity < ents.length())
			{
				entities::classes::CoreEntity *oldSelected = ents[edit_entity];
				entities::send_entity_event(oldSelected, entities::EntityEventDeselected());

				conoutf("ent deselected %i (%s)", i, oldSelected->name.c_str());
			}
			if (i >= 0 && i < ents.length())
			{
				entities::classes::CoreEntity *newSelected = ents[i];
				entities::send_entity_event(newSelected, entities::EntityEventSelected());

				conoutf("ent selected %i (%s)", i, newSelected->name.c_str());
			}
			
			edit_entity = i;
		}
	}

	float dropheight(entities::classes::CoreEntity *e)
	{
//		if(e->game_type==FLAG) return 0.0f;
		return 4.0f;
	}
#endif
}
