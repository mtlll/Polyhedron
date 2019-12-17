// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void defershader(int * a, const char * b, const char * c);
extern void forceshader(const char * a);
extern void shader(int * a, char * b, char * c, char * d);
extern void variantshader(int * a, char * b, int * c, char * d, char * e, int * f);
extern void setshader(char * a);
extern void dumpshader(const char * a, int * b, int * c);
extern void isshaderdefined(char * a);
extern void setuniformparam(char * a, float * b, CommandTypes::OptionalFloat c, CommandTypes::OptionalFloat d, float * e);
extern void setshaderparam(char * a, float * b, CommandTypes::OptionalFloat c, CommandTypes::OptionalFloat d, float * e);
extern void defuniformparam(char * a, float * b, CommandTypes::OptionalFloat c, CommandTypes::OptionalFloat d, float * e);
extern void reuseuniformparam(char * a, float * b, CommandTypes::OptionalFloat c, CommandTypes::OptionalFloat d, float * e);
extern void clearpostfx();
extern void addpostfx_scriptimpl(char * a, int * b, int * c, char * d, float * e, float * f, float * g, float * h);
extern void setpostfx(char * a, float * b, float * c, float * d, float * e);
extern void resetshaders();

static bool __dummy_defershader_bool = addcommand("defershader", (identfun)defershader, "iss", ID_COMMAND, "");

static bool __dummy_forceshader_bool = addcommand("forceshader", (identfun)forceshader, "s", ID_COMMAND, "");

static bool __dummy_shader_bool = addcommand("shader", (identfun)shader, "isss", ID_COMMAND, "");

static bool __dummy_variantshader_bool = addcommand("variantshader", (identfun)variantshader, "isissi", ID_COMMAND, "");

static bool __dummy_setshader_bool = addcommand("setshader", (identfun)setshader, "s", ID_COMMAND, "");

static bool __dummy_dumpshader_bool = addcommand("dumpshader", (identfun)dumpshader, "sii", ID_COMMAND, "");

static bool __dummy_isshaderdefined_bool = addcommand("isshaderdefined", (identfun)isshaderdefined, "s", ID_COMMAND, "");

static bool __dummy_setuniformparam_bool = addcommand("setuniformparam", (identfun)setuniformparam, "sfFFf", ID_COMMAND, "");

static bool __dummy_setshaderparam_bool = addcommand("setshaderparam", (identfun)setshaderparam, "sfFFf", ID_COMMAND, "");

static bool __dummy_defuniformparam_bool = addcommand("defuniformparam", (identfun)defuniformparam, "sfFFf", ID_COMMAND, "");

static bool __dummy_reuseuniformparam_bool = addcommand("reuseuniformparam", (identfun)reuseuniformparam, "sfFFf", ID_COMMAND, "");

static bool __dummy_clearpostfx_bool = addcommand("clearpostfx", (identfun)clearpostfx, "", ID_COMMAND, "");

static bool __dummy_addpostfx_bool = addcommand("addpostfx", (identfun)addpostfx_scriptimpl, "siisffff", ID_COMMAND, "");

static bool __dummy_setpostfx_bool = addcommand("setpostfx", (identfun)setpostfx, "sffff", ID_COMMAND, "");

static bool __dummy_resetshaders_bool = addcommand("resetshaders", (identfun)resetshaders, "", ID_COMMAND, "");



    // cubeScriptProto = iss
    // cppArgumentTypes = ['int *', 'const char *', 'const char *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['int * a', 'const char * b', 'const char * c']
    // cppOriginalFunctionName = defershader
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = defershader
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['const char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['const char * a']
    // cppOriginalFunctionName = forceshader
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = forceshader
    

    // cubeScriptProto = isss
    // cppArgumentTypes = ['int *', 'char *', 'char *', 'char *']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'char * b', 'char * c', 'char * d']
    // cppOriginalFunctionName = shader
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = shader
    

    // cubeScriptProto = isissi
    // cppArgumentTypes = ['int *', 'char *', 'int *', 'char *', 'char *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f']
    // cppArgumentDecls = ['int * a', 'char * b', 'int * c', 'char * d', 'char * e', 'int * f']
    // cppOriginalFunctionName = variantshader
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = variantshader
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = setshader
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = setshader
    

    // cubeScriptProto = sii
    // cppArgumentTypes = ['const char *', 'int *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['const char * a', 'int * b', 'int * c']
    // cppOriginalFunctionName = dumpshader
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = dumpshader
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = isshaderdefined
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = isshaderdefined
    

    // cubeScriptProto = sfFFf
    // cppArgumentTypes = ['char *', 'float *', 'CommandTypes::OptionalFloat', 'CommandTypes::OptionalFloat', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['char * a', 'float * b', 'CommandTypes::OptionalFloat c', 'CommandTypes::OptionalFloat d', 'float * e']
    // cppOriginalFunctionName = setuniformparam
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = setuniformparam
    

    // cubeScriptProto = sfFFf
    // cppArgumentTypes = ['char *', 'float *', 'CommandTypes::OptionalFloat', 'CommandTypes::OptionalFloat', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['char * a', 'float * b', 'CommandTypes::OptionalFloat c', 'CommandTypes::OptionalFloat d', 'float * e']
    // cppOriginalFunctionName = setshaderparam
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = setshaderparam
    

    // cubeScriptProto = sfFFf
    // cppArgumentTypes = ['char *', 'float *', 'CommandTypes::OptionalFloat', 'CommandTypes::OptionalFloat', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['char * a', 'float * b', 'CommandTypes::OptionalFloat c', 'CommandTypes::OptionalFloat d', 'float * e']
    // cppOriginalFunctionName = defuniformparam
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = defuniformparam
    

    // cubeScriptProto = sfFFf
    // cppArgumentTypes = ['char *', 'float *', 'CommandTypes::OptionalFloat', 'CommandTypes::OptionalFloat', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['char * a', 'float * b', 'CommandTypes::OptionalFloat c', 'CommandTypes::OptionalFloat d', 'float * e']
    // cppOriginalFunctionName = reuseuniformparam
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = reuseuniformparam
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearpostfx
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearpostfx
    

    // cubeScriptProto = siisffff
    // cppArgumentTypes = ['char *', 'int *', 'int *', 'char *', 'float *', 'float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']
    // cppArgumentDecls = ['char * a', 'int * b', 'int * c', 'char * d', 'float * e', 'float * f', 'float * g', 'float * h']
    // cppOriginalFunctionName = addpostfx_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = addpostfx
    

    // cubeScriptProto = sffff
    // cppArgumentTypes = ['char *', 'float *', 'float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['char * a', 'float * b', 'float * c', 'float * d', 'float * e']
    // cppOriginalFunctionName = setpostfx
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = setpostfx
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = resetshaders
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = resetshaders
    


