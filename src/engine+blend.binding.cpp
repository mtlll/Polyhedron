// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void optimizeblendmap_scriptimpl();
extern void dumpblendtexs();
extern void clearblendbrushes();
extern void delblendbrush(const char * a);
extern void addblendbrush(const char * a, const char * b);
extern void nextblendbrush(int * a);
extern void setblendbrush(char * a);
extern void getblendbrushname(int * a);
extern void curblendbrush();
extern void rotateblendbrush(int * a);
extern void paintblendmap_scriptimpl(int * a);
extern void clearblendmapsel();
extern void invertblendmapsel();
extern void invertblendmap_scriptimpl();
extern void showblendmap();
extern void clearblendmap();
extern void moveblendmap_scriptimpl(int * a, int * b);

static bool __dummy_optimizeblendmap_bool = addcommand("optimizeblendmap", (identfun)optimizeblendmap_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_dumpblendtexs_bool = addcommand("dumpblendtexs", (identfun)dumpblendtexs, "", ID_COMMAND, "");

static bool __dummy_clearblendbrushes_bool = addcommand("clearblendbrushes", (identfun)clearblendbrushes, "", ID_COMMAND, "");

static bool __dummy_delblendbrush_bool = addcommand("delblendbrush", (identfun)delblendbrush, "s", ID_COMMAND, "");

static bool __dummy_addblendbrush_bool = addcommand("addblendbrush", (identfun)addblendbrush, "ss", ID_COMMAND, "");

static bool __dummy_nextblendbrush_bool = addcommand("nextblendbrush", (identfun)nextblendbrush, "i", ID_COMMAND, "");

static bool __dummy_setblendbrush_bool = addcommand("setblendbrush", (identfun)setblendbrush, "s", ID_COMMAND, "");

static bool __dummy_getblendbrushname_bool = addcommand("getblendbrushname", (identfun)getblendbrushname, "i", ID_COMMAND, "");

static bool __dummy_curblendbrush_bool = addcommand("curblendbrush", (identfun)curblendbrush, "", ID_COMMAND, "");

static bool __dummy_rotateblendbrush_bool = addcommand("rotateblendbrush", (identfun)rotateblendbrush, "i", ID_COMMAND, "");

static bool __dummy_paintblendmap_bool = addcommand("paintblendmap", (identfun)paintblendmap_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_clearblendmapsel_bool = addcommand("clearblendmapsel", (identfun)clearblendmapsel, "", ID_COMMAND, "");

static bool __dummy_invertblendmapsel_bool = addcommand("invertblendmapsel", (identfun)invertblendmapsel, "", ID_COMMAND, "");

static bool __dummy_invertblendmap_bool = addcommand("invertblendmap", (identfun)invertblendmap_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_showblendmap_bool = addcommand("showblendmap", (identfun)showblendmap, "", ID_COMMAND, "");

static bool __dummy_clearblendmap_bool = addcommand("clearblendmap", (identfun)clearblendmap, "", ID_COMMAND, "");

static bool __dummy_moveblendmap_bool = addcommand("moveblendmap", (identfun)moveblendmap_scriptimpl, "ii", ID_COMMAND, "");



    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = optimizeblendmap_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = optimizeblendmap
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = dumpblendtexs
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = dumpblendtexs
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearblendbrushes
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearblendbrushes
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['const char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['const char * a']
    // cppOriginalFunctionName = delblendbrush
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = delblendbrush
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['const char *', 'const char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['const char * a', 'const char * b']
    // cppOriginalFunctionName = addblendbrush
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = addblendbrush
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = nextblendbrush
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = nextblendbrush
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = setblendbrush
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = setblendbrush
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = getblendbrushname
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getblendbrushname
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = curblendbrush
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = curblendbrush
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = rotateblendbrush
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = rotateblendbrush
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = paintblendmap_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = paintblendmap
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearblendmapsel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearblendmapsel
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = invertblendmapsel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = invertblendmapsel
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = invertblendmap_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = invertblendmap
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = showblendmap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = showblendmap
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearblendmap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearblendmap
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = moveblendmap_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = moveblendmap
    


