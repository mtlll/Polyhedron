// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void entcancel();
extern void entadd(int a);
extern void entflip();
extern void entrotate(int * a);
extern void entadd_scriptimpl();
extern void enttoggle_scriptimpl();
extern void entmoving_scriptimpl(CommandTypes::Boolean a);
extern void entpush(int * a);
extern void entautoview(int * a);
extern void delent();
extern void dropent();
extern void attachent();
extern void newent(char * a, int * b, int * c, int * d, int * e, int * f);
extern void newgent(char * a, char * b, char * c, char * d, char * e, char * f, char * g, char * h, char * i);
extern void entcopy();
extern void entpaste();
extern void entreplace();
extern void entset(char * a, int * b, int * c, int * d, int * e, int * f);
extern void nearestent();
extern void enthavesel();
extern void entselect(CommandTypes::Expression a);
extern void entloop(CommandTypes::Expression a);
extern void insel();
extern void entget();
extern void entindex();
extern void enttype(char * a, CommandTypes::ArgLen b);
extern void entattr(int * a, int * b, CommandTypes::ArgLen c);
extern void shrinkmap();
extern void newmap(int * a);
extern void mapenlarge();
extern void mapname();

static bool __dummy_entcancel_bool = addcommand("entcancel", (identfun)entcancel, "", ID_COMMAND, "");

static bool __dummy_enteditv_bool = addcommand("enteditv", (identfun)entadd, "i", ID_COMMAND, "");

static bool __dummy_entflip_bool = addcommand("entflip", (identfun)entflip, "", ID_COMMAND, "");

static bool __dummy_entrotate_bool = addcommand("entrotate", (identfun)entrotate, "i", ID_COMMAND, "");

static bool __dummy_entadd_bool = addcommand("entadd", (identfun)entadd_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_enttoggle_bool = addcommand("enttoggle", (identfun)enttoggle_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_entmoving_bool = addcommand("entmoving", (identfun)entmoving_scriptimpl, "b", ID_COMMAND, "");

static bool __dummy_entpush_bool = addcommand("entpush", (identfun)entpush, "i", ID_COMMAND, "");

static bool __dummy_entautoview_bool = addcommand("entautoview", (identfun)entautoview, "i", ID_COMMAND, "");

static bool __dummy_delent_bool = addcommand("delent", (identfun)delent, "", ID_COMMAND, "");

static bool __dummy_dropent_bool = addcommand("dropent", (identfun)dropent, "", ID_COMMAND, "");

static bool __dummy_attachent_bool = addcommand("attachent", (identfun)attachent, "", ID_COMMAND, "");

static bool __dummy_newent_bool = addcommand("newent", (identfun)newent, "siiiii", ID_COMMAND, "");

static bool __dummy_newgent_bool = addcommand("newgent", (identfun)newgent, "sssssssss", ID_COMMAND, "");

static bool __dummy_entcopy_bool = addcommand("entcopy", (identfun)entcopy, "", ID_COMMAND, "");

static bool __dummy_entpaste_bool = addcommand("entpaste", (identfun)entpaste, "", ID_COMMAND, "");

static bool __dummy_entreplace_bool = addcommand("entreplace", (identfun)entreplace, "", ID_COMMAND, "");

static bool __dummy_entset_bool = addcommand("entset", (identfun)entset, "siiiii", ID_COMMAND, "");

static bool __dummy_nearestent_bool = addcommand("nearestent", (identfun)nearestent, "", ID_COMMAND, "");

static bool __dummy_enthavesel_bool = addcommand("enthavesel", (identfun)enthavesel, "", ID_COMMAND, "");

static bool __dummy_entselect_bool = addcommand("entselect", (identfun)entselect, "e", ID_COMMAND, "");

static bool __dummy_entloop_bool = addcommand("entloop", (identfun)entloop, "e", ID_COMMAND, "");

static bool __dummy_insel_bool = addcommand("insel", (identfun)insel, "", ID_COMMAND, "");

static bool __dummy_entget_bool = addcommand("entget", (identfun)entget, "", ID_COMMAND, "");

static bool __dummy_entindex_bool = addcommand("entindex", (identfun)entindex, "", ID_COMMAND, "");

static bool __dummy_enttype_bool = addcommand("enttype", (identfun)enttype, "sN", ID_COMMAND, "");

static bool __dummy_entattr_bool = addcommand("entattr", (identfun)entattr, "iiN", ID_COMMAND, "");

static bool __dummy_shrinkmap_bool = addcommand("shrinkmap", (identfun)shrinkmap, "", ID_COMMAND, "");

static bool __dummy_newmap_bool = addcommand("newmap", (identfun)newmap, "i", ID_COMMAND, "");

static bool __dummy_mapenlarge_bool = addcommand("mapenlarge", (identfun)mapenlarge, "", ID_COMMAND, "");

static bool __dummy_mapname_bool = addcommand("mapname", (identfun)mapname, "", ID_COMMAND, "");



    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = entcancel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entcancel
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int a']
    // cppOriginalFunctionName = entadd
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = enteditv
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = entflip
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entflip
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = entrotate
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entrotate
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = entadd_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entadd
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = enttoggle_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = enttoggle
    

    // cubeScriptProto = b
    // cppArgumentTypes = ['CommandTypes::Boolean']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Boolean a']
    // cppOriginalFunctionName = entmoving_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entmoving
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = entpush
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entpush
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = entautoview
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entautoview
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = delent
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = delent
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = dropent
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = dropent
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = attachent
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = attachent
    

    // cubeScriptProto = siiiii
    // cppArgumentTypes = ['char *', 'int *', 'int *', 'int *', 'int *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f']
    // cppArgumentDecls = ['char * a', 'int * b', 'int * c', 'int * d', 'int * e', 'int * f']
    // cppOriginalFunctionName = newent
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = newent
    

    // cubeScriptProto = sssssssss
    // cppArgumentTypes = ['char *', 'char *', 'char *', 'char *', 'char *', 'char *', 'char *', 'char *', 'char *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i']
    // cppArgumentDecls = ['char * a', 'char * b', 'char * c', 'char * d', 'char * e', 'char * f', 'char * g', 'char * h', 'char * i']
    // cppOriginalFunctionName = newgent
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = newgent
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = entcopy
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entcopy
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = entpaste
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entpaste
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = entreplace
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entreplace
    

    // cubeScriptProto = siiiii
    // cppArgumentTypes = ['char *', 'int *', 'int *', 'int *', 'int *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f']
    // cppArgumentDecls = ['char * a', 'int * b', 'int * c', 'int * d', 'int * e', 'int * f']
    // cppOriginalFunctionName = entset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entset
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = nearestent
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = nearestent
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = enthavesel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = enthavesel
    

    // cubeScriptProto = e
    // cppArgumentTypes = ['CommandTypes::Expression']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Expression a']
    // cppOriginalFunctionName = entselect
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entselect
    

    // cubeScriptProto = e
    // cppArgumentTypes = ['CommandTypes::Expression']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Expression a']
    // cppOriginalFunctionName = entloop
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entloop
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = insel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = insel
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = entget
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entget
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = entindex
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entindex
    

    // cubeScriptProto = sN
    // cppArgumentTypes = ['char *', 'CommandTypes::ArgLen']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'CommandTypes::ArgLen b']
    // cppOriginalFunctionName = enttype
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = enttype
    

    // cubeScriptProto = iiN
    // cppArgumentTypes = ['int *', 'int *', 'CommandTypes::ArgLen']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['int * a', 'int * b', 'CommandTypes::ArgLen c']
    // cppOriginalFunctionName = entattr
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = entattr
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = shrinkmap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = shrinkmap
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = newmap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = newmap
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = mapenlarge
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mapenlarge
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = mapname
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mapname
    


