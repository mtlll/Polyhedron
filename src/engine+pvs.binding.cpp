// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void clearpvs();
extern void testpvs(int * a);
extern void genpvs(int * a);
extern void pvsstats();

static bool __dummy_clearpvs_bool = addcommand("clearpvs", (identfun)clearpvs, "", ID_COMMAND, "pvs");

static bool __dummy_testpvs_bool = addcommand("testpvs", (identfun)testpvs, "i", ID_COMMAND, "");

static bool __dummy_genpvs_bool = addcommand("genpvs", (identfun)genpvs, "i", ID_COMMAND, "");

static bool __dummy_pvsstats_bool = addcommand("pvsstats", (identfun)pvsstats, "", ID_COMMAND, "");



    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearpvs
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearpvs
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = testpvs
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = testpvs
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = genpvs
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = genpvs
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = pvsstats
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = pvsstats
    


