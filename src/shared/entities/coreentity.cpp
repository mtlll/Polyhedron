#include "cube.h"
#include "ents.h"
#include "game.h"
#include "ents.h"
#include "baseentity.h"
#include "coreentity.h"
#include "entityfactory.h"
#include <vector>
#include <string>
#include <variant>

extern void boxs3D(const vec &o, vec s, int g);
extern void boxs(int orient, vec o, const vec &s);
extern void boxs(int orient, vec o, const vec &s, float size);

ADD_ENTITY_TO_FACTORY(CoreEntity, "core_entity");


bool entities::classes::CoreEntity::spawned() const
{
    return (flags&entities::EntityFlags::EF_SPAWNED) != 0;
}

void entities::classes::CoreEntity::setspawned(bool val)
{
    if(val)
        flags |= entities::EntityFlags::EF_SPAWNED;
    else
        flags &= ~entities::EntityFlags::EF_SPAWNED;
}

void entities::classes::CoreEntity::setspawned()
{
    flags |= entities::EntityFlags::EF_SPAWNED;
}

void entities::classes::CoreEntity::clearspawned()
{
    flags &= ~entities::EntityFlags::EF_SPAWNED;
}

void entities::classes::CoreEntity::onSelected(bool selected)
{
	this->selected = selected;
}

void entities::classes::CoreEntity::saveToJsonImpl(nlohmann::json& document)
{
	document[classname] = {};
	to_json(document[classname], *this);
}


void entities::classes::CoreEntity::saveToJson(nlohmann::json& document)
{
	document = {
		{"class", currentClassname()},
		{"et_type", et_type},
		{"ent_type", ent_type},
		{"game_type", game_type}
	};
	
	saveToJsonImpl(document);
}

void entities::classes::CoreEntity::fromJsonImpl(const nlohmann::json& document)
{
	document.at(classname).get_to(*this);
}

void entities::classes::CoreEntity::loadFromJson(const nlohmann::json& document)
{
	document.at("et_type").get_to(et_type);
	document.at("ent_type").get_to(ent_type);
	document.at("game_type").get_to(game_type);

	fromJsonImpl(document);
}

void entities::classes::CoreEntity::setAttribute(const std::string &key, const entities::attribute_T &value)
{
	setAttributeImpl(key, value);
}

entities::attribute_T entities::classes::CoreEntity::getAttribute(const std::string &key) const
{
	return getAttributeImpl(key);
}

bool entities::classes::CoreEntity::getBoundingBox(int entselradius, ivec &minbb, ivec &maxbb) const
{
	if (et_type == ET_EMPTY)
	{
		return false;
	}
	
	minbb = ivec(vec(o).sub(entselradius));
	maxbb = ivec(vec(o).add(entselradius+1));
	return true;
}

void entities::classes::CoreEntity::renderForEdit()
{

}

void entities::classes::CoreEntity::renderForEditGui()
{

}

void entities::classes::CoreEntity::renderSelected(int entselradius, int entorient)
{
	gle::colorub(0, 40, 0);
	vec es(entselradius);
    vec eo = o;
    eo.sub(es);
    es.mul(2);
    
	boxs3D(eo, es, 1);
}


void entities::classes::CoreEntity::renderHighlight(int entselradius, int entorient, float thickness)
{
	gle::colorub(0, 40, 0);
	vec es(entselradius);
    vec eo = o;
    eo.sub(es);
    es.mul(2);
    
	boxs3D(eo, es, 1);

	gle::colorub(200,0,0);
	boxs(entorient, eo, es, thickness);
}

void entities::classes::CoreEntity::renderMoveShadow(int entselradius, int size)
{
	vec es(entselradius);
    vec eo = o;
    eo.sub(es);
    es.mul(2);

	vec a, b;
	gle::colorub(20, 20, 20);
	(a = eo).x = eo.x - fmod(eo.x, size); (b = es).x = a.x + size; boxs3D(a, b, 1);
	(a = eo).y = eo.y - fmod(eo.y, size); (b = es).y = a.x + size; boxs3D(a, b, 1);
	(a = eo).z = eo.z - fmod(eo.z, size); (b = es).z = a.x + size; boxs3D(a, b, 1);
}

void entities::classes::from_json(const nlohmann::json& document,  entities::classes::CoreEntity* entity_ptr)
{
	std::string name;
	document.get_to(name);
}

void entities::classes::to_json(nlohmann::json& document, const entities::classes::CoreEntity* entity_ptr)
{
	if (entity_ptr)
	{
		document = nlohmann::json {entity_ptr->name};
	}
	else
	{
		document = "";
	}
}



