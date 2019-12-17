// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void glext(char * a);
extern void getcamyaw();
extern void getcampitch();
extern void getcamroll();
extern void getcampos();
extern void loadcrosshair_(const char * a, int * b);
extern void getcrosshair(int * a);

static bool __dummy_glext_bool = addcommand("glext", (identfun)glext, "s", ID_COMMAND, "");

static bool __dummy_getcamyaw_bool = addcommand("getcamyaw", (identfun)getcamyaw, "", ID_COMMAND, "");

static bool __dummy_getcampitch_bool = addcommand("getcampitch", (identfun)getcampitch, "", ID_COMMAND, "");

static bool __dummy_getcamroll_bool = addcommand("getcamroll", (identfun)getcamroll, "", ID_COMMAND, "");

static bool __dummy_getcampos_bool = addcommand("getcampos", (identfun)getcampos, "", ID_COMMAND, "");

static bool __dummy_loadcrosshair_bool = addcommand("loadcrosshair", (identfun)loadcrosshair_, "si", ID_COMMAND, "");

static bool __dummy_getcrosshair_bool = addcommand("getcrosshair", (identfun)getcrosshair, "i", ID_COMMAND, "");



    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = glext
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = glext
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = getcamyaw
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getcamyaw
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = getcampitch
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getcampitch
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = getcamroll
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getcamroll
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = getcampos
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getcampos
    

    // cubeScriptProto = si
    // cppArgumentTypes = ['const char *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['const char * a', 'int * b']
    // cppOriginalFunctionName = loadcrosshair_
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = loadcrosshair
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = getcrosshair
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getcrosshair
    


