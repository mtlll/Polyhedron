// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void applychanges();
extern void pendingchanges(int * a);

static bool __dummy_applychanges_bool = addcommand("applychanges", (identfun)applychanges, "", ID_COMMAND, "");

static bool __dummy_pendingchanges_bool = addcommand("pendingchanges", (identfun)pendingchanges, "i", ID_COMMAND, "");



    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = applychanges
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = applychanges
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = pendingchanges
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = pendingchanges
    


