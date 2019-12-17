// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void IsConnected_scriptimpl(CommandTypes::Boolean a, CommandTypes::Boolean b);
extern void ConnectedIP();
extern void connectedport();
extern void ConnectServ(const char * a, int b, const char * c);
extern void Reconnect(const char * a);
extern void LanConnect(int * a, char * b);
extern void disconnect_scriptimpl(int * a);
extern void localconnect_scriptimpl();
extern void LocalDisconnect_scriptimpl();

static bool __dummy_IsConnected_bool = addcommand("IsConnected", (identfun)IsConnected_scriptimpl, "bb", ID_COMMAND, "");

static bool __dummy_connectedip_bool = addcommand("connectedip", (identfun)ConnectedIP, "", ID_COMMAND, "");

static bool __dummy_connectedport_bool = addcommand("connectedport", (identfun)connectedport, "", ID_COMMAND, "");

static bool __dummy_connect_bool = addcommand("connect", (identfun)ConnectServ, "sis", ID_COMMAND, "");

static bool __dummy_reconnect_bool = addcommand("reconnect", (identfun)Reconnect, "s", ID_COMMAND, "");

static bool __dummy_lanconnect_bool = addcommand("lanconnect", (identfun)LanConnect, "is", ID_COMMAND, "");

static bool __dummy_disconnect_bool = addcommand("disconnect", (identfun)disconnect_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_localconnect_bool = addcommand("localconnect", (identfun)localconnect_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_localdisconnect_bool = addcommand("localdisconnect", (identfun)LocalDisconnect_scriptimpl, "", ID_COMMAND, "");



    // cubeScriptProto = bb
    // cppArgumentTypes = ['CommandTypes::Boolean', 'CommandTypes::Boolean']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['CommandTypes::Boolean a', 'CommandTypes::Boolean b']
    // cppOriginalFunctionName = IsConnected_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = IsConnected
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = ConnectedIP
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = connectedip
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = connectedport
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = connectedport
    

    // cubeScriptProto = sis
    // cppArgumentTypes = ['const char *', 'int', 'const char *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['const char * a', 'int b', 'const char * c']
    // cppOriginalFunctionName = ConnectServ
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = connect
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['const char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['const char * a']
    // cppOriginalFunctionName = Reconnect
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = reconnect
    

    // cubeScriptProto = is
    // cppArgumentTypes = ['int *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'char * b']
    // cppOriginalFunctionName = LanConnect
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = lanconnect
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = disconnect_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = disconnect
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = localconnect_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = localconnect
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = LocalDisconnect_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = localdisconnect
    


