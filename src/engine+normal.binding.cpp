// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void smoothangle_scriptimpl(int * a, int * b);

static bool __dummy_smoothangle_bool = addcommand("smoothangle", (identfun)smoothangle_scriptimpl, "ii", ID_COMMAND, "");



    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = smoothangle_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = smoothangle
    


