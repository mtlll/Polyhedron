// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void fullconsole(int * a, CommandTypes::ArgLen b, ident * c);
extern void toggleconsole();
extern void conskip_scriptimpl(int * a);
extern void miniconskip_scriptimpl(int * a);
extern void clearconsole();
extern void keymap(int * a, char * b);
extern void bind_scriptimpl(char * a, char * b);
extern void specbind(char * a, char * b);
extern void editbind(char * a, char * b);
extern void getbind_scriptimpl(char * a);
extern void getspecbind(char * a);
extern void geteditbind(char * a);
extern void searchbinds_scriptimpl(char * a);
extern void searchspecbinds(char * a);
extern void searcheditbinds(char * a);
extern void clearbinds();
extern void clearspecbinds();
extern void cleareditbinds();
extern void clearallbinds();
extern void inputcommand(char * a, char * b, char * c, char * d);
extern void saycommand(char * a);
extern void history_(int * a);
extern void onrelease(const char * a);
extern void addfilecomplete(char * a, char * b, char * c);
extern void addlistcomplete(char * a, char * b);

static bool __dummy_fullconsole_bool = addcommand("fullconsole", (identfun)fullconsole, "iNr", ID_COMMAND, "");

static bool __dummy_toggleconsole_bool = addcommand("toggleconsole", (identfun)toggleconsole, "", ID_COMMAND, "");

static bool __dummy_conskip_bool = addcommand("conskip", (identfun)conskip_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_miniconskip_bool = addcommand("miniconskip", (identfun)miniconskip_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_clearconsole_bool = addcommand("clearconsole", (identfun)clearconsole, "", ID_COMMAND, "");

static bool __dummy_keymap_bool = addcommand("keymap", (identfun)keymap, "is", ID_COMMAND, "");

static bool __dummy_bind_bool = addcommand("bind", (identfun)bind_scriptimpl, "ss", ID_COMMAND, "");

static bool __dummy_specbind_bool = addcommand("specbind", (identfun)specbind, "ss", ID_COMMAND, "");

static bool __dummy_editbind_bool = addcommand("editbind", (identfun)editbind, "ss", ID_COMMAND, "");

static bool __dummy_getbind_bool = addcommand("getbind", (identfun)getbind_scriptimpl, "s", ID_COMMAND, "");

static bool __dummy_getspecbind_bool = addcommand("getspecbind", (identfun)getspecbind, "s", ID_COMMAND, "");

static bool __dummy_geteditbind_bool = addcommand("geteditbind", (identfun)geteditbind, "s", ID_COMMAND, "");

static bool __dummy_searchbinds_bool = addcommand("searchbinds", (identfun)searchbinds_scriptimpl, "s", ID_COMMAND, "");

static bool __dummy_searchspecbinds_bool = addcommand("searchspecbinds", (identfun)searchspecbinds, "s", ID_COMMAND, "");

static bool __dummy_searcheditbinds_bool = addcommand("searcheditbinds", (identfun)searcheditbinds, "s", ID_COMMAND, "");

static bool __dummy_clearbinds_bool = addcommand("clearbinds", (identfun)clearbinds, "", ID_COMMAND, "");

static bool __dummy_clearspecbinds_bool = addcommand("clearspecbinds", (identfun)clearspecbinds, "", ID_COMMAND, "");

static bool __dummy_cleareditbinds_bool = addcommand("cleareditbinds", (identfun)cleareditbinds, "", ID_COMMAND, "");

static bool __dummy_clearallbinds_bool = addcommand("clearallbinds", (identfun)clearallbinds, "", ID_COMMAND, "");

static bool __dummy_inputcommand_bool = addcommand("inputcommand", (identfun)inputcommand, "ssss", ID_COMMAND, "");

static bool __dummy_saycommand_bool = addcommand("saycommand", (identfun)saycommand, "s", ID_COMMAND, "");

static bool __dummy_history_bool = addcommand("history", (identfun)history_, "i", ID_COMMAND, "");

static bool __dummy_onrelease_bool = addcommand("onrelease", (identfun)onrelease, "s", ID_COMMAND, "");

static bool __dummy_complete_bool = addcommand("complete", (identfun)addfilecomplete, "sss", ID_COMMAND, "");

static bool __dummy_listcomplete_bool = addcommand("listcomplete", (identfun)addlistcomplete, "ss", ID_COMMAND, "");



    // cubeScriptProto = iNr
    // cppArgumentTypes = ['int *', 'CommandTypes::ArgLen', 'ident *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['int * a', 'CommandTypes::ArgLen b', 'ident * c']
    // cppOriginalFunctionName = fullconsole
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fullconsole
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = toggleconsole
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = toggleconsole
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = conskip_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = conskip
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = miniconskip_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = miniconskip
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearconsole
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearconsole
    

    // cubeScriptProto = is
    // cppArgumentTypes = ['int *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'char * b']
    // cppOriginalFunctionName = keymap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = keymap
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = bind_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = bind
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = specbind
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = specbind
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = editbind
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = editbind
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = getbind_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getbind
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = getspecbind
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getspecbind
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = geteditbind
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = geteditbind
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = searchbinds_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = searchbinds
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = searchspecbinds
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = searchspecbinds
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = searcheditbinds
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = searcheditbinds
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearbinds
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearbinds
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearspecbinds
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearspecbinds
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = cleareditbinds
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = cleareditbinds
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearallbinds
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearallbinds
    

    // cubeScriptProto = ssss
    // cppArgumentTypes = ['char *', 'char *', 'char *', 'char *']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['char * a', 'char * b', 'char * c', 'char * d']
    // cppOriginalFunctionName = inputcommand
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = inputcommand
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = saycommand
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = saycommand
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = history_
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = history
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['const char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['const char * a']
    // cppOriginalFunctionName = onrelease
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = onrelease
    

    // cubeScriptProto = sss
    // cppArgumentTypes = ['char *', 'char *', 'char *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['char * a', 'char * b', 'char * c']
    // cppOriginalFunctionName = addfilecomplete
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = complete
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = addlistcomplete
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = listcomplete
    


