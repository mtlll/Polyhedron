// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void moving_scriptimpl(int * a);
extern void cubecancel();
extern void cancelsel();
extern void reorient();
extern void selextend();
extern void edittoggle();
extern void selmoved();
extern void selsave();
extern void selrestore();
extern void selswap();
extern void havesel_scriptimpl();
extern void selchildcount_scriptimpl();
extern void selchildmat_scriptimpl(char * a);
extern void clearundos();
extern void editundo();
extern void editredo();
extern void delprefab(char * a);
extern void saveprefab(char * a);
extern void pasteprefab(char * a);
extern void copy();
extern void pastehilite();
extern void paste();
namespace hmap { extern void cancel(); }
namespace hmap { extern void select(); }
namespace hmap { extern void clearhbrush(); }
namespace hmap { extern void hbrushvert(int * a, int * b, int * c); }
extern void editface(int * a, int * b);
extern void pushsel(int * a);
extern void delcube();
extern void vdelta(CommandTypes::Expression a);
extern void vrotate(int * a);
extern void voffset(int * a, int * b);
extern void vscroll(float * a, float * b);
extern void vscale(float * a);
extern void vlayer(int * a);
extern void vdetail(int * a);
extern void valpha(float * a, float * b);
extern void vcolor(float * a, float * b, float * c);
extern void vrefract(float * a, float * b, float * c, float * d);
extern void vreset();
extern void vshaderparam(const char * a, float * b, float * c, float * d, float * e);
extern void edittex_(int * a);
extern void gettex();
extern void getcurtex();
extern void getseltex();
extern void gettexname(int * a, int * b);
extern void getslottex(int * a);
extern void settex(int * a);
extern void getreptex();
extern void texmru_scriptimpl(int * a);
extern void looptexmru(ident * a, CommandTypes::Expression b);
extern void numvslots();
extern void numslots();
extern void replace_scriptimpl();
extern void replacesel();
extern void flip();
extern void rotate(int * a);
extern void editmat(char * a, char * b);

static bool __dummy_moving_bool = addcommand("moving", (identfun)moving_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_cubecancel_bool = addcommand("cubecancel", (identfun)cubecancel, "", ID_COMMAND, "");

static bool __dummy_cancelsel_bool = addcommand("cancelsel", (identfun)cancelsel, "", ID_COMMAND, "octaedit");

static bool __dummy_reorient_bool = addcommand("reorient", (identfun)reorient, "", ID_COMMAND, "");

static bool __dummy_selextend_bool = addcommand("selextend", (identfun)selextend, "", ID_COMMAND, "");

static bool __dummy_edittoggle_bool = addcommand("edittoggle", (identfun)edittoggle, "", ID_COMMAND, "");

static bool __dummy_selmoved_bool = addcommand("selmoved", (identfun)selmoved, "", ID_COMMAND, "");

static bool __dummy_selsave_bool = addcommand("selsave", (identfun)selsave, "", ID_COMMAND, "");

static bool __dummy_selrestore_bool = addcommand("selrestore", (identfun)selrestore, "", ID_COMMAND, "");

static bool __dummy_selswap_bool = addcommand("selswap", (identfun)selswap, "", ID_COMMAND, "");

static bool __dummy_havesel_bool = addcommand("havesel", (identfun)havesel_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_selchildcount_bool = addcommand("selchildcount", (identfun)selchildcount_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_selchildmat_bool = addcommand("selchildmat", (identfun)selchildmat_scriptimpl, "s", ID_COMMAND, "");

static bool __dummy_clearundos_bool = addcommand("clearundos", (identfun)clearundos, "", ID_COMMAND, "");

static bool __dummy_undo_bool = addcommand("undo", (identfun)editundo, "", ID_COMMAND, "");

static bool __dummy_redo_bool = addcommand("redo", (identfun)editredo, "", ID_COMMAND, "");

static bool __dummy_delprefab_bool = addcommand("delprefab", (identfun)delprefab, "s", ID_COMMAND, "");

static bool __dummy_saveprefab_bool = addcommand("saveprefab", (identfun)saveprefab, "s", ID_COMMAND, "");

static bool __dummy_pasteprefab_bool = addcommand("pasteprefab", (identfun)pasteprefab, "s", ID_COMMAND, "");

static bool __dummy_copy_bool = addcommand("copy", (identfun)copy, "", ID_COMMAND, "");

static bool __dummy_pastehilite_bool = addcommand("pastehilite", (identfun)pastehilite, "", ID_COMMAND, "");

static bool __dummy_paste_bool = addcommand("paste", (identfun)paste, "", ID_COMMAND, "");

static bool __dummy_cancel_bool = addcommand("cancel", (identfun)hmap::cancel, "", ID_COMMAND, "");

static bool __dummy_select_bool = addcommand("select", (identfun)hmap::select, "", ID_COMMAND, "");

static bool __dummy_clearhbrush_bool = addcommand("clearhbrush", (identfun)hmap::clearhbrush, "", ID_COMMAND, "");

static bool __dummy_hbrushvert_bool = addcommand("hbrushvert", (identfun)hmap::hbrushvert, "iii", ID_COMMAND, "");

static bool __dummy_editface_bool = addcommand("editface", (identfun)editface, "ii", ID_COMMAND, "");

static bool __dummy_pushsel_bool = addcommand("pushsel", (identfun)pushsel, "i", ID_COMMAND, "");

static bool __dummy_delcube_bool = addcommand("delcube", (identfun)delcube, "", ID_COMMAND, "");

static bool __dummy_vdelta_bool = addcommand("vdelta", (identfun)vdelta, "e", ID_COMMAND, "");

static bool __dummy_vrotate_bool = addcommand("vrotate", (identfun)vrotate, "i", ID_COMMAND, "");

static bool __dummy_voffset_bool = addcommand("voffset", (identfun)voffset, "ii", ID_COMMAND, "");

static bool __dummy_vscroll_bool = addcommand("vscroll", (identfun)vscroll, "ff", ID_COMMAND, "");

static bool __dummy_vscale_bool = addcommand("vscale", (identfun)vscale, "f", ID_COMMAND, "");

static bool __dummy_vlayer_bool = addcommand("vlayer", (identfun)vlayer, "i", ID_COMMAND, "");

static bool __dummy_vdetail_bool = addcommand("vdetail", (identfun)vdetail, "i", ID_COMMAND, "");

static bool __dummy_valpha_bool = addcommand("valpha", (identfun)valpha, "ff", ID_COMMAND, "");

static bool __dummy_vcolor_bool = addcommand("vcolor", (identfun)vcolor, "fff", ID_COMMAND, "");

static bool __dummy_vrefract_bool = addcommand("vrefract", (identfun)vrefract, "ffff", ID_COMMAND, "");

static bool __dummy_vreset_bool = addcommand("vreset", (identfun)vreset, "", ID_COMMAND, "");

static bool __dummy_vshaderparam_bool = addcommand("vshaderparam", (identfun)vshaderparam, "sffff", ID_COMMAND, "");

static bool __dummy_edittext_bool = addcommand("edittext", (identfun)edittex_, "i", ID_COMMAND, "");

static bool __dummy_gettex_bool = addcommand("gettex", (identfun)gettex, "", ID_COMMAND, "");

static bool __dummy_getcurtex_bool = addcommand("getcurtex", (identfun)getcurtex, "", ID_COMMAND, "");

static bool __dummy_getseltex_bool = addcommand("getseltex", (identfun)getseltex, "", ID_COMMAND, "");

static bool __dummy_gettexname_bool = addcommand("gettexname", (identfun)gettexname, "ii", ID_COMMAND, "");

static bool __dummy_getslottex_bool = addcommand("getslottex", (identfun)getslottex, "i", ID_COMMAND, "");

static bool __dummy_settex_bool = addcommand("settex", (identfun)settex, "i", ID_COMMAND, "");

static bool __dummy_getreptex_bool = addcommand("getreptex", (identfun)getreptex, "", ID_COMMAND, "");

static bool __dummy_texmru_bool = addcommand("texmru", (identfun)texmru_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_looptexmru_bool = addcommand("looptexmru", (identfun)looptexmru, "re", ID_COMMAND, "");

static bool __dummy_numvslots_bool = addcommand("numvslots", (identfun)numvslots, "", ID_COMMAND, "");

static bool __dummy_numslots_bool = addcommand("numslots", (identfun)numslots, "", ID_COMMAND, "");

static bool __dummy_replace_bool = addcommand("replace", (identfun)replace_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_replacesel_bool = addcommand("replacesel", (identfun)replacesel, "", ID_COMMAND, "");

static bool __dummy_flip_bool = addcommand("flip", (identfun)flip, "", ID_COMMAND, "");

static bool __dummy_rotate_bool = addcommand("rotate", (identfun)rotate, "i", ID_COMMAND, "");

static bool __dummy_editmat_bool = addcommand("editmat", (identfun)editmat, "ss", ID_COMMAND, "");



    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = moving_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = moving
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = cubecancel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = cubecancel
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = cancelsel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = cancelsel
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = reorient
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = reorient
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = selextend
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = selextend
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = edittoggle
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = edittoggle
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = selmoved
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = selmoved
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = selsave
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = selsave
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = selrestore
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = selrestore
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = selswap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = selswap
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = havesel_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = havesel
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = selchildcount_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = selchildcount
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = selchildmat_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = selchildmat
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearundos
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearundos
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = editundo
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = undo
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = editredo
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = redo
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = delprefab
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = delprefab
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = saveprefab
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = saveprefab
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = pasteprefab
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = pasteprefab
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = copy
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = copy
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = pastehilite
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = pastehilite
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = paste
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = paste
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = cancel
    // cppReturnType = void
    // cppNamespaceHierarchy = ['hmap']
    // bindWithFunctionName = cancel
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = select
    // cppReturnType = void
    // cppNamespaceHierarchy = ['hmap']
    // bindWithFunctionName = select
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = clearhbrush
    // cppReturnType = void
    // cppNamespaceHierarchy = ['hmap']
    // bindWithFunctionName = clearhbrush
    

    // cubeScriptProto = iii
    // cppArgumentTypes = ['int *', 'int *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['int * a', 'int * b', 'int * c']
    // cppOriginalFunctionName = hbrushvert
    // cppReturnType = void
    // cppNamespaceHierarchy = ['hmap']
    // bindWithFunctionName = hbrushvert
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = editface
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = editface
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = pushsel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = pushsel
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = delcube
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = delcube
    

    // cubeScriptProto = e
    // cppArgumentTypes = ['CommandTypes::Expression']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Expression a']
    // cppOriginalFunctionName = vdelta
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vdelta
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = vrotate
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vrotate
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = voffset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = voffset
    

    // cubeScriptProto = ff
    // cppArgumentTypes = ['float *', 'float *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'float * b']
    // cppOriginalFunctionName = vscroll
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vscroll
    

    // cubeScriptProto = f
    // cppArgumentTypes = ['float *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['float * a']
    // cppOriginalFunctionName = vscale
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vscale
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = vlayer
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vlayer
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = vdetail
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vdetail
    

    // cubeScriptProto = ff
    // cppArgumentTypes = ['float *', 'float *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'float * b']
    // cppOriginalFunctionName = valpha
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = valpha
    

    // cubeScriptProto = fff
    // cppArgumentTypes = ['float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c']
    // cppOriginalFunctionName = vcolor
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vcolor
    

    // cubeScriptProto = ffff
    // cppArgumentTypes = ['float *', 'float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c', 'float * d']
    // cppOriginalFunctionName = vrefract
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vrefract
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = vreset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vreset
    

    // cubeScriptProto = sffff
    // cppArgumentTypes = ['const char *', 'float *', 'float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['const char * a', 'float * b', 'float * c', 'float * d', 'float * e']
    // cppOriginalFunctionName = vshaderparam
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = vshaderparam
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = edittex_
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = edittext
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = gettex
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = gettex
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = getcurtex
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getcurtex
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = getseltex
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getseltex
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = gettexname
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = gettexname
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = getslottex
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getslottex
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = settex
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = settex
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = getreptex
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = getreptex
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = texmru_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texmru
    

    // cubeScriptProto = re
    // cppArgumentTypes = ['ident *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['ident * a', 'CommandTypes::Expression b']
    // cppOriginalFunctionName = looptexmru
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = looptexmru
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = numvslots
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = numvslots
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = numslots
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = numslots
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = replace_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = replace
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = replacesel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = replacesel
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = flip
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = flip
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = rotate
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = rotate
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = editmat
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = editmat
    


