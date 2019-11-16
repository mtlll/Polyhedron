#include "entityfactory.h"
#include "cube.h"
#include "game.h"
#include "ents.h"
#include "coreentity.h"
#include "baseentity.h"

namespace {
	const std::string fallbackEntityType = "base_entity";
}


template <> std::string entities::AttributeVisitCoercer<std::string>::operator()(std::string const& value) const
{
	return value;
}

template <> std::string entities::AttributeVisitCoercer<std::string>::operator()(float value) const
{
	return std::to_string(value);
}

template <> std::string entities::AttributeVisitCoercer<std::string>::operator()(int value) const
{
	return std::to_string(value);
}

template <> std::string entities::AttributeVisitCoercer<std::string>::operator()(bool value) const
{
	return std::to_string(value);
}


template <> float entities::AttributeVisitCoercer<float>::operator()(const std::string& value) const
{
	return std::stof(value);
}

template <> float entities::AttributeVisitCoercer<float>::operator()(const float value) const
{
	return value;
}

template <> float entities::AttributeVisitCoercer<float>::operator()(const int value) const
{
	return round(value);
}

template <> float entities::AttributeVisitCoercer<float>::operator()(const bool value) const
{
	return value ? 1.0f : 0.0f;
}


template <> int entities::AttributeVisitCoercer<int>::operator()(std::string const& value) const
{
	return std::stoi(value);
}

template <> int entities::AttributeVisitCoercer<int>::operator()(float value) const
{
	return value;
}

template <> int entities::AttributeVisitCoercer<int>::operator()(int value) const
{
	return value;
}

template <> int entities::AttributeVisitCoercer<int>::operator()(bool value) const
{
	return value ? 1 : 0;
}


template <> bool entities::AttributeVisitCoercer<bool>::operator()(const std::string& value) const
{
	return value == "true" || value == "1" || value == "True" || value == "TRUE" || std::stoi(value) != 0 || std::stof(value) != 0.0f ? true : false;
}

template <> bool entities::AttributeVisitCoercer<bool>::operator()(const float value) const
{
	return value != 0.0f ? true : false;
}

template <> bool entities::AttributeVisitCoercer<bool>::operator()(const int value) const
{
	return value != 0 ? true : false;
}

template <> bool entities::AttributeVisitCoercer<bool>::operator()(const bool value) const
{
	return value;
}

std::map<std::string, entities::EntityFactory::EntityFactoryConstructor>& entities::EntityFactory::getConstructors()
{
	static std::map<std::string, EntityFactoryConstructor> s_ConstructorList;
	
	return s_ConstructorList;
}


std::map<std::string, entities::EntityFactory::EntityFactoryAttribute>& entities::EntityFactory::getAttributors()
{
	static std::map<std::string, EntityFactoryAttribute> s_AttributorList;
	
	return s_AttributorList;
}


void entities::EntityFactory::addEntityFactory(const std::string &classname, EntityFactory::EntityFactoryConstructor constructor, EntityFactory::EntityFactoryAttribute attributor)
{
	auto& constructorList = getConstructors();
	
	if (constructorList.find(classname) != constructorList.end())
	{
		printf("Entity Constructor Factory for class '%s' already exists!\n", classname.c_str());
		return;
	}
	
	auto& attributorList = getAttributors();
	
	if (attributorList.find(classname) != attributorList.end())
	{
		printf("Entity Attributor Factory for class '%s' already exists!\n", classname.c_str());
		return;
	}

	printf("Entity Factory for class '%s' registered\n", classname.c_str());
	constructorList[classname] = constructor;
	attributorList[classname] = attributor;
}

// Constructs the entity by using the special macro generated EntityNameConstruct function.
entities::classes::CoreEntity* entities::EntityFactory::constructEntity(const std::string &classname)
{
	auto& constructorList = getConstructors();

	if (constructorList.find(classname) == constructorList.end())
	{
		conoutf(CON_WARN, "Entity Factory for class '%s' missing!", classname.c_str());
		return constructorList.at(fallbackEntityType)();
	}
	else
	{
		conoutf("Constructed class: %s", classname.c_str());
		return constructorList.at(classname)();
	}
}


entities::attributeList_T entities::EntityFactory::attributes(const std::string &classname)
{
	auto& attributorList = getAttributors();

	if (attributorList.find(classname) == attributorList.end())
	{
		conoutf(CON_WARN, "Entity Factory for class '%s' missing!", classname.c_str());
		return attributorList.at(fallbackEntityType)();
	}
	else
	{
		return attributorList.at(classname)();
	}
}


SCRIPTEXPORT void loop_all_entities(ident *id, CommandTypes::Expression body)
{
    loopstart(id, stack);
    for(auto factoryPair : entities::EntityFactory::getAttributors())
    {
		loopiter(id, stack, factoryPair.first.c_str());
		execute(body);
    }
    loopend(id, stack);
}


SCRIPTEXPORT void get_ent_attributes(char* entityname, ident *id, CommandTypes::Expression body)
{
    loopstart(id, stack);
    for(auto row : entities::EntityFactory::attributes(entityname))
    {
		for(auto col : row)
		{
			try {
				if (std::holds_alternative<std::string>(col))
				{
					loopiter(id, stack, std::get<std::string>(col).c_str());
				}
				else if (std::holds_alternative<float>(col))
				{
					loopiter(id, stack, std::get<float>(col));
				}
				else if (std::holds_alternative<int>(col))
				{
					loopiter(id, stack, std::get<int>(col));
				}
				else if (std::holds_alternative<bool>(col))
				{
					loopiter(id, stack, std::get<bool>(col) ? 1 : 0);
				}
				else
				{
					loopiter(id, stack, nullptr);
				}
			}
			catch(std::bad_variant_access& e)
			{
				std::string accessError = "A_ERROR(" + std::string(e.what()) + ")";
				loopiter(id, stack, accessError.c_str());
			}
			execute(body);
		}
    }
    loopend(id, stack);
}
