import re

CUSTOM_TOJSON_VARGENERATORS = {}
CUSTOM_FROMJSON_VARGENERATORS = {}

def Generate(cxxRootNode):
    from ..cppmodel.CxxClass import CxxClass
    
    template = """#include "{}"
{}"""
    generated_funcs = []
    for node in cxxRootNode.forEachChild(noDepth = True):
        if type(node) is CxxClass:
            generated_funcs.append(GenerateFromJson(node))
            generated_funcs.append(GenerateToJson(node))
            generated_funcs.append(GenerateAttributeDefinition(node))
            generated_funcs.append(GenerateAttributeGetter(node))
            generated_funcs.append(GenerateAttributeSetter(node))
            generated_funcs.append(GenerateJsonDebug(node))
    if len(generated_funcs) == 0:
        return ""

    headerFile = str(cxxRootNode)[:-4] + ".h"
    return template.format(headerFile, "\n".join(generated_funcs))

def GenerateJsonVariableTemplateValues(cxxVar):
    variableName = cxxVar.sourceObject.spelling
    variableType = cxxVar.sourceObject.type.spelling

    return {
        "variableName": variableName,
        "variableType": variableType
    }

def GenerateJsonTemplateValues(cxxClass):
    className = str(cxxClass)

    return {
        "className": className
    }

def GenerateToJson(cxxClass):
    templateValues = GenerateJsonTemplateValues(cxxClass)

    output = []
    for child in cxxClass.forEachChild(noDepth = True):
        output = output + GenerateToJsonVariable(child, "entity_t")
    body = ",\n\t\t".join(output)
    return cxxClass.namespaceBlock(f"""void to_json(nlohmann::json& document, const {templateValues['className']}& entity_t)
{{
\tdocument = {{
\t\t{body}
\t}};
}}
""")    

def GenerateToJsonVariable(cxxVar, instanceVar):
    templateValues = GenerateJsonVariableTemplateValues(cxxVar)
    output = []

    if templateValues["variableType"] in CUSTOM_TOJSON_VARGENERATORS:
        output = output + CUSTOM_TOJSON_VARGENERATORS[templateValues["variableType"]](templateValues)
    else:
        output.append(f"{{\"{templateValues['variableName']}\", {instanceVar}.{templateValues['variableName']}}}")
    return output


def GenerateFromJson(cxxClass):
    templateValues = GenerateJsonTemplateValues(cxxClass)

    output = []
    for child in cxxClass.forEachChild(noDepth = True):
        output = output + GenerateFromJsonVariable(child, "document", "entity_t")
    body = "\n\t".join(output)
    return cxxClass.namespaceBlock(f"""void from_json(const nlohmann::json& document,  {templateValues['className']}& entity_t)
{{
\t{body}
}}
""")

def GenerateFromJsonVariable(cxxVar, jsonRootVar, instanceVar):
    templateValues = GenerateJsonVariableTemplateValues(cxxVar)
    output = []

    if templateValues["variableType"] in CUSTOM_FROMJSON_VARGENERATORS:
        output = output + CUSTOM_FROMJSON_VARGENERATORS[templateValues["variableType"]](templateValues)
    else:
        output.append(f"if (document.find(\"{templateValues['variableName']}\") != document.end()) {jsonRootVar}.at(\"{templateValues['variableName']}\").get_to({instanceVar}.{templateValues['variableName']});")
    return output


def GenerateAttributeDefinition(cxxClass):
    templateValues = GenerateJsonTemplateValues(cxxClass)

    output = []
    for child in cxxClass.forEachChild(noDepth = True):
        output = output + GenerateAttributeDefinitionVariable(child)
    if len(output) > 0:
        output = [f"{{\"header\"s, \"{cxxClass}\"s}}"] + output
    body = ",\n\t\t".join(output)
    return f"""const entities::attributeList_T {templateValues['className']}::attributes()
{{
    using namespace std::string_literals;

    return entities::attributeList_T {{
        {body}
    }};
}}
"""

def GenerateAttributeDefinitionVariable(cxxVar):
    templateValues = GenerateJsonVariableTemplateValues(cxxVar)
    output = []
    definition = []

    for child in cxxVar.forEachChild(noDepth = True):
        phui, uiType, *data = child.data
        definition.append(f"\"{uiType}\"s")
        definition.append(f"\"{cxxVar}\"s")
        for element in data:
            definition.append(GenerateAttributeDefinitionVariableSanitized(element))

    if len(definition) > 0:
        output.append(
            "{" + ", ".join(definition) + "}"
        )

    return output

def GenerateAttributeDefinitionVariableSanitized(element):
    if re.match('^[a-zA-Z][a-zA-Z0-9]*', element):
        return f"\"{element}\"s"
    if re.match('^-?[0-9.]+$', element):
        if re.match('[^.]', element):
            return str(int(element))
        else:
            return str(float(element)) + "f"
    if element.startswith("\"") and element.endswith("\""):
        return f"{element}s"
    else:
        return f"\"{element}\"s"

def GenerateAttributeGetter(cxxClass):
    templateValues = GenerateJsonTemplateValues(cxxClass)
    hasElse = ""

    output = []
    for child in cxxClass.forEachChild(noDepth = True):
        output = output + GenerateAttributeGetterVariable(child, hasElse)

        if len(output) > 0:
            hasElse = "else "

    body = "\n\t".join(output)
    return f"""entities::attribute_T {templateValues['className']}::getAttributeImpl(const std::string &key) const
{{
\t{body}
}}
"""

def GenerateAttributeGetterVariable(cxxVar, hasElse):
    templateValues = GenerateJsonVariableTemplateValues(cxxVar)
    output = []

    for child in cxxVar.forEachChild(noDepth = True):
        phui, uiType, *data = child.data

        output.append(f"""{hasElse}if (key == "{cxxVar}")
	{{
		return {cxxVar};
	}}""")

    return output

def GenerateAttributeSetter(cxxClass):
    templateValues = GenerateJsonTemplateValues(cxxClass)
    hasElse = ""

    output = []
    for child in cxxClass.forEachChild(noDepth = True):
        output = output + GenerateAttributeSetterVariable(child, hasElse)

        if len(output) > 0:
            hasElse = "else "

    body = "\n\t".join(output)
    return f"""void {templateValues['className']}::setAttributeImpl(const std::string &key, const entities::attribute_T &value)
{{
\tEntityEventAttributeChanged changedEvent(key);
\t{body}
}}
"""

def GenerateAttributeSetterVariable(cxxVar, hasElse):
    templateValues = GenerateJsonVariableTemplateValues(cxxVar)
    output = []

    cxxClass = cxxVar.parent

    for child in cxxVar.forEachChild(noDepth = True):
        phui, uiType, *data = child.data

        output.append(f"""{hasElse}if (key == "{cxxVar}")
	{{
        if (std::holds_alternative<decltype({cxxVar})>(value))
        {{
		    {cxxVar} = std::get<decltype({cxxVar})>(value);
        }}
        else
        {{
			{cxxVar} = std::visit(AttributeVisitCoercer<decltype({cxxVar})>(), value);
        }}
        onImpl(changedEvent);
	}}""")

    return output


def GenerateJsonDebug(cxxClass):
    debug_output = []
    for child in cxxClass.forEachChild():
        debug_output.append(GenerateJsonVariableDebug(child))
    
    return "\n".join(debug_output)

def GenerateJsonVariableDebug(cxxVar):
    templateValues = GenerateJsonVariableTemplateValues(cxxVar)

    output = ["// type:  " + str(type(cxxVar))]
    for key in templateValues:
        output.append(f"// {key} => {templateValues[key]}")
    return "\n".join(output)

# ---- Custom Generators for specific variable types

# def CustomVarGenerator_toJson_vec(templateValues):
#     output_obj = []
#     for m in ['x', 'y', 'z']:
#         output_obj.append(f"\"{m}\", {templateValues['variableName']}.{m}")
#     return [f"\"{templateValues['variableName']}\""] + ["{{" + ", ".join(output_obj) + "}}"]

# def CustomVarGenerator_toJson_vec4(templateValues):
#     output_obj = []
#     for m in ['x', 'y', 'z', 'w']:
#         output_obj.append(f"\"{m}\", {templateValues['variableName']}.{m}")
#     return [f"\"{templateValues['variableName']}\""] + ["{{" + ", ".join(output_obj) + "}}"]

# CUSTOM_TOJSON_VARGENERATORS['vec'] = CustomVarGenerator_toJson_vec
# CUSTOM_TOJSON_VARGENERATORS['vec4'] = CustomVarGenerator_toJson_vec4