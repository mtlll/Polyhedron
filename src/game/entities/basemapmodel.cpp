#include "engine/engine.h"
#include "game/game.h"

#include "basemapmodel.h"
#include "shared/entities/entityfactory.h"

namespace {
	static inline void transformbb(const entities::classes::CoreEntity *e, vec &center, vec &radius)
	{
		if(e->attr5 > 0) { float scale = e->attr5/100.0f; center.mul(scale); radius.mul(scale); }
		rotatebb(center, radius, e->attr2, e->attr3, e->attr4);
	}

	static inline void mmboundbox(const entities::classes::CoreEntity *e, model *m, vec &center, vec &radius)
	{
		m->boundbox(center, radius);
		transformbb(e, center, radius);
	}
}

namespace entities {
namespace classes {

BaseMapModel::BaseMapModel()
{
	et_type = MAPMODEL;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
    physstate = PHYS_FALL;
    collidetype = COLLIDE_TRI;

    setAttribute("name", "model");
}

BaseMapModel::BaseMapModel(const std::string &filename) : BaseMapModel() {
	this->filename = filename;
	preloadMapModel(filename);
}


void BaseMapModel::preload() {
	preloadMapModel(filename);
}

void BaseMapModel::think() {

}

void BaseMapModel::render() {

}

bool BaseMapModel::getBoundingBox(int entselradius, ivec &minbb, ivec &maxbb) const
{
    if(model *m = loadmapmodel(model_idx))
    {
        vec center, radius;
        mmboundbox(this, m, center, radius);
        center.add(o);
        radius.max(entselradius);
        minbb = ivec(vec(center).sub(radius));
        maxbb = ivec(vec(center).add(radius).add(1));

        return true;
    }

    return false;
}


void BaseMapModel::onAttributeSet(const std::string &key, const std::string &value) {
    if (key == "model" && filename != value) {
		filename = value;
        preload();
    }
}

void BaseMapModel::onAnimate(int &anim, int &basetime) {
    conoutf("OnAnimate: %i %i", anim, basetime);
}

void BaseMapModel::preloadMapModel(const std::string &filename) {
    // In case this is the first time, a filename will be supplied for sure.
    if (!filename.empty()) {
        mmi = mapmodels.add();
        mmi.m = loadmodel(filename.c_str(), -1, true);
        mmi.collide = loadmodel(filename.c_str(), -1, true);
        copycubestr(mmi.name, filename.c_str());

        // Copy into mmi.
//		mmi = loadmodelinfo(filename.c_str(), this);
		//mapmodels.add();
        model_idx = mapmodels.length() + 1;
    } else {
        preloadMapModel("world/box");
    }
}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(BaseMapModel, "base_map_model", BaseDynamicEntity);
