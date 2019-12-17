// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void quit();
extern void screenres(int a, int b);
extern void resetgl();
extern void getfps_scriptimpl(int * a);
extern void testlog(char * a);

static bool __dummy_quit_bool = addcommand("quit", (identfun)quit, "", ID_COMMAND, "");

static bool __dummy_screenres_bool = addcommand("screenres", (identfun)screenres, "ii", ID_COMMAND, "");

static bool __dummy_resetgl_bool = addcommand("resetgl", (identfun)resetgl, "", ID_COMMAND, "Called whenever CHANGE_GFX or CHANGE_SHADERS is supposed to be there.");

static bool __dummy_getfps_bool = addcommand("getfps", (identfun)getfps_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_testlog_bool = addcommand("testlog", (identfun)testlog, "s", ID_COMMAND, "");



    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = quit
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = quit
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int', 'int']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int a', 'int b']
    // cppOriginalFunctionName = screenres
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = screenres
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = resetgl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = resetgl
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = getfps_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getfps
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = testlog
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = testlog
    


