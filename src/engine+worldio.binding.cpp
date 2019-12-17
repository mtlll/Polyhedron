// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void fixmapname(char * a);
extern void mapcfgname();
extern void savecurrentmap();
extern void savemap(char * a);
extern void loadmap(char * a);
extern void writeobj(char * a);
extern void writecollideobj(char * a);

static bool __dummy_fixmapname_bool = addcommand("fixmapname", (identfun)fixmapname, "s", ID_COMMAND, "Make the name of the map great again (tm)");

static bool __dummy_mapcfgname_bool = addcommand("mapcfgname", (identfun)mapcfgname, "", ID_COMMAND, "");

static bool __dummy_savecurrentmap_bool = addcommand("savecurrentmap", (identfun)savecurrentmap, "", ID_COMMAND, "");

static bool __dummy_savemap_bool = addcommand("savemap", (identfun)savemap, "s", ID_COMMAND, "");

static bool __dummy_map_bool = addcommand("map", (identfun)loadmap, "s", ID_COMMAND, "");

static bool __dummy_writeobj_bool = addcommand("writeobj", (identfun)writeobj, "s", ID_COMMAND, "");

static bool __dummy_writecollideobj_bool = addcommand("writecollideobj", (identfun)writecollideobj, "s", ID_COMMAND, "");



    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = fixmapname
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fixmapname
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = mapcfgname
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mapcfgname
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = savecurrentmap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = savecurrentmap
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = savemap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = savemap
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = loadmap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = map
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = writeobj
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = writeobj
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = writecollideobj
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = writecollideobj
    


