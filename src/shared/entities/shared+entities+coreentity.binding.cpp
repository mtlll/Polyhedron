

#include "/Users/micha/dev/ScMaMike/src/shared/entities/coreentity.h"
namespace entities {
namespace classes {
void from_json(const nlohmann::json& document,  entities::classes::CoreEntity& entity_t)
{
	if (document.find("o") != document.end()) document.at("o").get_to(entity_t.o);
	if (document.find("attr1") != document.end()) document.at("attr1").get_to(entity_t.attr1);
	if (document.find("attr2") != document.end()) document.at("attr2").get_to(entity_t.attr2);
	if (document.find("attr3") != document.end()) document.at("attr3").get_to(entity_t.attr3);
	if (document.find("attr4") != document.end()) document.at("attr4").get_to(entity_t.attr4);
	if (document.find("attr5") != document.end()) document.at("attr5").get_to(entity_t.attr5);
	if (document.find("reserved") != document.end()) document.at("reserved").get_to(entity_t.reserved);
	if (document.find("model_idx") != document.end()) document.at("model_idx").get_to(entity_t.model_idx);
	if (document.find("flags") != document.end()) document.at("flags").get_to(entity_t.flags);
	if (document.find("attached") != document.end()) document.at("attached").get_to(entity_t.attached);
	if (document.find("name") != document.end()) document.at("name").get_to(entity_t.name);
}

}
}
namespace entities {
namespace classes {
void to_json(nlohmann::json& document, const entities::classes::CoreEntity& entity_t)
{
	document = {
		{"o", entity_t.o},
		{"attr1", entity_t.attr1},
		{"attr2", entity_t.attr2},
		{"attr3", entity_t.attr3},
		{"attr4", entity_t.attr4},
		{"attr5", entity_t.attr5},
		{"reserved", entity_t.reserved},
		{"model_idx", entity_t.model_idx},
		{"flags", entity_t.flags},
		{"attached", entity_t.attached},
		{"name", entity_t.name}
	};
}

}
}
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => o
// variableType => vec
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => attr1
// variableType => short
// type:  <class 'autobind.cppmodel.PhuiElement.PhuiElement'>
// variableName => phui;"Attribute 1";slider;-180;180;1
// variableType => 
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => attr2
// variableType => short
// type:  <class 'autobind.cppmodel.PhuiElement.PhuiElement'>
// variableName => phui;"Attribute 2";checkbox
// variableType => 
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => attr3
// variableType => short
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => attr4
// variableType => short
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => attr5
// variableType => short
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => reserved
// variableType => uchar
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => model_idx
// variableType => short
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => flags
// variableType => int
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => attached
// variableType => entities::classes::CoreEntity *
// type:  <class 'autobind.cppmodel.CxxVariable.CxxVariable'>
// variableName => name
// variableType => std::string
// type:  <class 'autobind.cppmodel.PhuiElement.PhuiElement'>
// variableName => phui;"Name (for triggers)";input
// variableType => 