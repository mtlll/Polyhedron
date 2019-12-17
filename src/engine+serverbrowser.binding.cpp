// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

namespace game { extern void sortservers(); }
namespace game { extern void RefreshServers(); }
namespace game { extern void NumServers(); }
namespace game { extern void ServerInfoValid(int * a); }
namespace game { extern void ServerInfoDescription(int * a); }
namespace game { extern void ServerInfoName(int * a); }
namespace game { extern void ServInfoPort(int * a); }
namespace game { extern void ServerInfoHasPassword(int * a); }
namespace game { extern void ServerInfoKeep(int * a); }
namespace game { extern void ServerInfoMap(int * a); }
namespace game { extern void ServerInfoPing(int * a); }
namespace game { extern void ServerInfoNumberOfPlayers(int * a); }
namespace game { extern void ServerInfoMaxPlayers(int * a); }
namespace game { extern void ServerInfoPlayers(int * a); }
namespace game { extern void ServerInfoAttribute(int * a, int * b); }
namespace game { extern void ConnectServinfo(int * a, char * b); }
namespace game { extern void UpdateFromMaster(); }
namespace game { extern void InitServers(); }
namespace game { extern void addserver_scriptimpl(const char * a, int * b, const char * c); }
namespace game { extern void KeepServer(const char * a, int * b, const char * c); }
namespace game { extern void clearservers_scriptimpl(int * a); }

static bool __dummy_sortservers_bool = addcommand("sortservers", (identfun)game::sortservers, "", ID_COMMAND, "");

static bool __dummy_refreshservers_bool = addcommand("refreshservers", (identfun)game::RefreshServers, "", ID_COMMAND, "");

static bool __dummy_NumServers_bool = addcommand("NumServers", (identfun)game::NumServers, "", ID_COMMAND, "");

static bool __dummy_servinfovalid_bool = addcommand("servinfovalid", (identfun)game::ServerInfoValid, "i", ID_COMMAND, "");

static bool __dummy_servinfodesc_bool = addcommand("servinfodesc", (identfun)game::ServerInfoDescription, "i", ID_COMMAND, "");

static bool __dummy_servinfoname_bool = addcommand("servinfoname", (identfun)game::ServerInfoName, "i", ID_COMMAND, "");

static bool __dummy_servinfoport_bool = addcommand("servinfoport", (identfun)game::ServInfoPort, "i", ID_COMMAND, "");

static bool __dummy_servinfohaspassword_bool = addcommand("servinfohaspassword", (identfun)game::ServerInfoHasPassword, "i", ID_COMMAND, "");

static bool __dummy_servinfokeep_bool = addcommand("servinfokeep", (identfun)game::ServerInfoKeep, "i", ID_COMMAND, "");

static bool __dummy_servinfomap_bool = addcommand("servinfomap", (identfun)game::ServerInfoMap, "i", ID_COMMAND, "");

static bool __dummy_servinfoping_bool = addcommand("servinfoping", (identfun)game::ServerInfoPing, "i", ID_COMMAND, "");

static bool __dummy_servinfonumberOfPlayers_bool = addcommand("servinfonumberOfPlayers", (identfun)game::ServerInfoNumberOfPlayers, "i", ID_COMMAND, "");

static bool __dummy_servinfomaxPlayers_bool = addcommand("servinfomaxPlayers", (identfun)game::ServerInfoMaxPlayers, "i", ID_COMMAND, "");

static bool __dummy_servinfoplayers_bool = addcommand("servinfoplayers", (identfun)game::ServerInfoPlayers, "i", ID_COMMAND, "");

static bool __dummy_servinfoattr_bool = addcommand("servinfoattr", (identfun)game::ServerInfoAttribute, "ii", ID_COMMAND, "");

static bool __dummy_connectservinfo_bool = addcommand("connectservinfo", (identfun)game::ConnectServinfo, "is", ID_COMMAND, "");

static bool __dummy_updatefrommaster_bool = addcommand("updatefrommaster", (identfun)game::UpdateFromMaster, "", ID_COMMAND, "");

static bool __dummy_initservers_bool = addcommand("initservers", (identfun)game::InitServers, "", ID_COMMAND, "");

static bool __dummy_addserver_bool = addcommand("addserver", (identfun)game::addserver_scriptimpl, "sis", ID_COMMAND, "");

static bool __dummy_keepserver_bool = addcommand("keepserver", (identfun)game::KeepServer, "sis", ID_COMMAND, "");

static bool __dummy_clearservers_bool = addcommand("clearservers", (identfun)game::clearservers_scriptimpl, "i", ID_COMMAND, "");



    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = sortservers
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = sortservers
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = RefreshServers
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = refreshservers
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = NumServers
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = NumServers
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoValid
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfovalid
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoDescription
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfodesc
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoName
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfoname
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServInfoPort
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfoport
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoHasPassword
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfohaspassword
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoKeep
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfokeep
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoMap
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfomap
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoPing
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfoping
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoNumberOfPlayers
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfonumberOfPlayers
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoMaxPlayers
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfomaxPlayers
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = ServerInfoPlayers
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfoplayers
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = ServerInfoAttribute
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = servinfoattr
    

    // cubeScriptProto = is
    // cppArgumentTypes = ['int *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'char * b']
    // cppOriginalFunctionName = ConnectServinfo
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = connectservinfo
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = UpdateFromMaster
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = updatefrommaster
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = InitServers
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = initservers
    

    // cubeScriptProto = sis
    // cppArgumentTypes = ['const char *', 'int *', 'const char *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['const char * a', 'int * b', 'const char * c']
    // cppOriginalFunctionName = addserver_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = addserver
    

    // cubeScriptProto = sis
    // cppArgumentTypes = ['const char *', 'int *', 'const char *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['const char * a', 'int * b', 'const char * c']
    // cppOriginalFunctionName = KeepServer
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = keepserver
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = clearservers_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['game']
    // bindWithFunctionName = clearservers
    


