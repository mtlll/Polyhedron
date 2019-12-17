// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

namespace networking { extern void StartListenserver(int * a); }
namespace networking { extern void StopListenServer(); }

static bool __dummy_startlistenserver_bool = addcommand("startlistenserver", (identfun)networking::StartListenserver, "i", ID_COMMAND, "");

static bool __dummy_stoplistenserver_bool = addcommand("stoplistenserver", (identfun)networking::StopListenServer, "", ID_COMMAND, "");



    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = StartListenserver
    // cppReturnType = void
    // cppNamespaceHierarchy = ['networking']
    // bindWithFunctionName = startlistenserver
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = StopListenServer
    // cppReturnType = void
    // cppNamespaceHierarchy = ['networking']
    // bindWithFunctionName = stoplistenserver
    


