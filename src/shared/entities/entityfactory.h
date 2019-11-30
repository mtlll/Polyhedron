#pragma once
#include <string>
#include <map>
#include <functional>
#include <string>
#include <variant>


typedef unsigned int uint;
struct ident;
namespace CommandTypes
{
    typedef uint* Expression;
}

namespace entities {

	typedef std::variant<std::string, float, int, bool> attribute_T;
	typedef std::vector< std::vector< attribute_T > > attributeList_T;

	template <typename TargetType>
	struct AttributeVisitCoercer
	{
		TargetType operator()(const std::string& value) const;
		TargetType operator()(float value) const;
		TargetType operator()(int value) const;
		TargetType operator()(bool value) const;
	};

	namespace classes
	{
		class CoreEntity;
	}

    class EntityFactory
    {
    private:
        typedef std::function<entities::classes::CoreEntity*()> EntityFactoryConstructor;
        typedef std::function<attributeList_T()> EntityFactoryAttribute;

	public:
        static std::map<std::string, EntityFactoryConstructor>& getConstructors();
        static std::map<std::string, EntityFactoryAttribute>& getAttributors();
        
        template<class ET>
        static entities::classes::CoreEntity* constructor()
        {
			return static_cast<entities::classes::CoreEntity*>(new ET);
		}

        static void addEntityFactory(const std::string &classname, EntityFactoryConstructor constructor, EntityFactoryAttribute attributor);

        static entities::classes::CoreEntity* constructEntity(const std::string &classname);
		static attributeList_T attributes(const std::string &classname);
    };
}


#define ADD_ENTITY_TO_FACTORY(LOCALNAME, CLASSNAME) \
    const std::string entities::classes::LOCALNAME::classname = CLASSNAME;\
	std::string entities::classes::LOCALNAME::currentClassname() { return CLASSNAME; }\
	entities::classes::CoreEntity *entities::classes::LOCALNAME::Construct()\
	{\
		return entities::EntityFactory::constructor<entities::classes::LOCALNAME>(); \
	}\
	class LOCALNAME##Intializer\
	{\
	public:\
		LOCALNAME##Intializer()\
		{\
            entities::EntityFactory::addEntityFactory(CLASSNAME, &entities::classes::LOCALNAME::Construct, &entities::classes::LOCALNAME::attributes);\
		}\
    } LOCALNAME##IntializerInstance;


#define ADD_ENTITY_TO_FACTORY_SERIALIZED(LOCALNAME, CLASSNAME, DERIVED) \
	ADD_ENTITY_TO_FACTORY(LOCALNAME, CLASSNAME) \
	namespace entities { namespace classes {\
		extern void from_json(const nlohmann::json&, LOCALNAME&);\
		extern void to_json(nlohmann::json&, const LOCALNAME&);\
	} }\
	void entities::classes::LOCALNAME::fromJsonImpl(const nlohmann::json& document) {\
		document.at(CLASSNAME).get_to(*this);\
		DERIVED::fromJsonImpl(document);\
	}\
	void entities::classes::LOCALNAME::saveToJsonImpl(nlohmann::json& document) {\
		DERIVED::saveToJsonImpl(document);\
		document[CLASSNAME] = *this;\
	}\
	void entities::classes::LOCALNAME::setAttribute(const std::string &key, const entities::attribute_T &value) {\
		DERIVED::setAttribute(key, value);\
		setAttributeImpl(key, value);\
	}\
	entities::attribute_T entities::classes::LOCALNAME::getAttribute(const std::string &key) const {\
		entities::attribute_T attributeValue = DERIVED::getAttribute(key);\
		if (std::holds_alternative<std::string>(attributeValue) && std::get<std::string>(attributeValue).empty()) {\
			attributeValue = getAttributeImpl(key);\
		}\
		return attributeValue;\
	}\
	void entities::classes::LOCALNAME::onImpl(const Event& event) {\
		on(event);\
		DERIVED::onImpl(event);\
	}\
	void entities::classes::LOCALNAME::renderImpl(game::RenderPass pass) {\
		DERIVED::renderImpl(pass);\
		render(pass);\
	}

#define ENTITY_FACTORY_IMPL(LOCALNAME) \
	public:\
	friend class LOCALNAME##Intializer;\
	friend void from_json(const nlohmann::json&, LOCALNAME&);\
	friend void to_json(nlohmann::json&, const LOCALNAME&);\
    static const std::string classname;\
	virtual std::string currentClassname();\
	static CoreEntity *Construct();\
	virtual void fromJsonImpl(const nlohmann::json& document);\
    virtual void saveToJsonImpl(nlohmann::json& document);\
	virtual void setAttribute(const std::string &key, const attribute_T &value);\
	virtual attribute_T getAttribute(const std::string &key) const;\
	void setAttributeImpl(const std::string &key, const attribute_T &value);\
	attribute_T getAttributeImpl(const std::string &key) const;\
	static const attributeList_T attributes();\
	virtual void onImpl(const Event& event);\
	void on(const Event& event);\
	virtual void renderImpl(game::RenderPass pass);\
	void render(game::RenderPass pass);\
    virtual ~LOCALNAME() = default;
