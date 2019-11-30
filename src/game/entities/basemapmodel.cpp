#include "engine/engine.h"
#include "game/game.h"
#include "engine/world.h"

#include "basemapmodel.h"
#include "shared/entities/entityfactory.h"

//namespace {
//	static inline void transformbb(const entities::classes::CoreEntity *e, vec &center, vec &radius)
//	{
//		if(e->attr5 > 0) { float scale = e->attr5/100.0f; center.mul(scale); radius.mul(scale); }
//		rotatebb(center, radius, e->attr2, e->attr3, e->attr4);
//	}
//
//	static inline void mmboundbox(const entities::classes::CoreEntity *e, model *m, vec &center, vec &radius)
//	{
//		m->boundbox(center, radius);
//		transformbb(e, center, radius);
//	}
//}

//extern inline void transformbb(const entities::classes::CoreEntity *e, vec &center, vec &radius);
//extern inline void mmboundbox(const entities::classes::CoreEntity *e, model *m, vec &center, vec &radius);

namespace entities {
namespace classes {

BaseMapModel::BaseMapModel()
{
	et_type = ET_MAPMODEL;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
    physstate = PHYS_FALL;
    collidetype = COLLIDE_TRI;

    setAttribute("name", "model");
}

BaseMapModel::BaseMapModel(const std::string &modelname) : BaseMapModel() {
	this->modelname = modelname;
	preloadMapModel(modelname);
}


void BaseMapModel::preload() {
	preloadMapModel(modelname);
}

void BaseMapModel::think() {

}

void BaseMapModel::render(game::RenderPass pass)
{
	if (pass == game::RenderPass::Main)
	{
		rendermodel(modelname.c_str(), 0, o, yaw, pitch, 0, MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED);
	}
}

bool BaseMapModel::getBoundingBox(int entselradius, vec &minbb, vec &maxbb) const
{
    if(mmi.m)
    {
        vec center, radius;
        mmboundbox(this, mmi.m, center, radius);
        center.add(o);
        radius.max(entselradius);
        minbb = vec(center).sub(radius);
        maxbb = vec(center).add(radius).add(1);

        return true;
    }

    return BaseDynamicEntity::getBoundingBox(entselradius, minbb, maxbb);
}

void BaseMapModel::onAnimate(int &anim, int &basetime) {
    conoutf("OnAnimate: %i %i", anim, basetime);
}

void BaseMapModel::preloadMapModel(const std::string &modelname)
{
	if (model_idx >= 0)
	{
		// In case this is the first time, a filename will be supplied for sure.
		if (!modelname.empty())
		{
			mmi = mapmodels.add();
			mmi.m = loadmodel(modelname.c_str(), -1, true);
			if (mmi.m)
			{
				mmi.collide = loadmodel(modelname.c_str(), -1, true);
				copycubestr(mmi.name, modelname.c_str());

				model_idx = mapmodels.length() - 1;
			}
			else
			{
				conoutf("BaseMapModel::preloadMapModel: couldn't load model: %s\n", modelname.c_str());
			}
		}
		else
		{
			preloadMapModel("world/box");
		}
	}
}


const std::string& BaseMapModel::getModelName() const
{
	return modelname;
}

void BaseMapModel::on(const Event& event)
{
	switch(event.type)
	{
		case EntityEventType::AttributeChanged:
		{
			const EntityEventAttributeChanged& attrChangeEvent = static_cast<const EntityEventAttributeChanged&>(event);
			
			if (attrChangeEvent.payload == "modelname")
			{
				preload();
			}
		} break;
		case EntityEventType::HoverStart:
		break;
		case EntityEventType::HoverStop:
		break;
		case EntityEventType::SelectStart:
		break;
		case EntityEventType::SelectStop:
		break;
		case EntityEventType::TouchStart:
		break;
		case EntityEventType::TouchStop:
		break;
		case EntityEventType::Tick:
		break;
		case EntityEventType::Use:
		break;
		case EntityEventType::Trigger:
		break;
		case EntityEventType::Precache:
			preload();
		break;

		default:
		case EntityEventType::None:
		case EntityEventType::Count:
		break;
	}
}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(BaseMapModel, "base_map_model", BaseDynamicEntity);
