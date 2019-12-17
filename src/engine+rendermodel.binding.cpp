// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void mdlcullface(int * a);
extern void mdlcolor(float * a, float * b, float * c);
extern void mdlcollide(int * a);
extern void mdlellipsecollide(int * a);
extern void mdltricollide(char * a);
extern void mdlspec(float * a);
extern void mdlgloss(int * a);
extern void mdlalphatest(float * a);
extern void mdldepthoffset(int * a);
extern void mdlglow(float * a, float * b, float * c);
extern void mdlenvmap(float * a, float * b, char * c);
extern void mdlfullbright(float * a);
extern void mdlshader(char * a);
extern void mdlspin(float * a, float * b, float * c);
extern void mdlscale(float * a);
extern void mdltrans(float * a, float * b, float * c);
extern void mdlyaw(float * a);
extern void mdlpitch(float * a);
extern void mdlroll(float * a);
extern void mdlshadow(int * a);
extern void mdlalphashadow(int * a);
extern void mdlbb(float * a, float * b, float * c);
extern void mdlextendbb(float * a, float * b, float * c);
extern void mdlname();
extern void rdvert(float * a, float * b, float * c, float * d);
extern void rdeye(int * a);
extern void rdtri(int * a, int * b, int * c);
extern void rdjoint(int * a, int * b, int * c, int * d, int * e);
extern void rdlimitdist(int * a, int * b, float * c, float * d);
extern void rdlimitrot(int * a, int * b, float * c, float * d, float * e, float * f, float * g);
extern void rdanimjoints(int * a);
extern void mapmodel(char * a);
extern void mmodel(char * a);
extern void mapmodelreset(int * a);
extern void mapmodelname_scriptimpl(int * a, int * b);
extern void nummapmodels();
extern void clearmodel(char * a);
extern void findanims(char * a);

static bool __dummy_mdlcullface_bool = addcommand("mdlcullface", (identfun)mdlcullface, "i", ID_COMMAND, "");

static bool __dummy_mdlcolor_bool = addcommand("mdlcolor", (identfun)mdlcolor, "fff", ID_COMMAND, "");

static bool __dummy_mdlcollide_bool = addcommand("mdlcollide", (identfun)mdlcollide, "i", ID_COMMAND, "");

static bool __dummy_mdlellipsecollide_bool = addcommand("mdlellipsecollide", (identfun)mdlellipsecollide, "i", ID_COMMAND, "");

static bool __dummy_mdltricollide_bool = addcommand("mdltricollide", (identfun)mdltricollide, "s", ID_COMMAND, "");

static bool __dummy_mdlspec_bool = addcommand("mdlspec", (identfun)mdlspec, "f", ID_COMMAND, "");

static bool __dummy_mdlgloss_bool = addcommand("mdlgloss", (identfun)mdlgloss, "i", ID_COMMAND, "");

static bool __dummy_mdlalphatest_bool = addcommand("mdlalphatest", (identfun)mdlalphatest, "f", ID_COMMAND, "");

static bool __dummy_mdldepthoffset_bool = addcommand("mdldepthoffset", (identfun)mdldepthoffset, "i", ID_COMMAND, "");

static bool __dummy_mdlglow_bool = addcommand("mdlglow", (identfun)mdlglow, "fff", ID_COMMAND, "");

static bool __dummy_mdlenvmap_bool = addcommand("mdlenvmap", (identfun)mdlenvmap, "ffs", ID_COMMAND, "");

static bool __dummy_mdlfullbright_bool = addcommand("mdlfullbright", (identfun)mdlfullbright, "f", ID_COMMAND, "");

static bool __dummy_mdlshader_bool = addcommand("mdlshader", (identfun)mdlshader, "s", ID_COMMAND, "");

static bool __dummy_mdlspin_bool = addcommand("mdlspin", (identfun)mdlspin, "fff", ID_COMMAND, "");

static bool __dummy_mdlscale_bool = addcommand("mdlscale", (identfun)mdlscale, "f", ID_COMMAND, "");

static bool __dummy_mdltrans_bool = addcommand("mdltrans", (identfun)mdltrans, "fff", ID_COMMAND, "");

static bool __dummy_mdlyaw_bool = addcommand("mdlyaw", (identfun)mdlyaw, "f", ID_COMMAND, "");

static bool __dummy_mdlpitch_bool = addcommand("mdlpitch", (identfun)mdlpitch, "f", ID_COMMAND, "");

static bool __dummy_mdlroll_bool = addcommand("mdlroll", (identfun)mdlroll, "f", ID_COMMAND, "");

static bool __dummy_mdlshadow_bool = addcommand("mdlshadow", (identfun)mdlshadow, "i", ID_COMMAND, "");

static bool __dummy_mdlalphashadow_bool = addcommand("mdlalphashadow", (identfun)mdlalphashadow, "i", ID_COMMAND, "");

static bool __dummy_mdlbb_bool = addcommand("mdlbb", (identfun)mdlbb, "fff", ID_COMMAND, "");

static bool __dummy_mdlextendbb_bool = addcommand("mdlextendbb", (identfun)mdlextendbb, "fff", ID_COMMAND, "");

static bool __dummy_mdlname_bool = addcommand("mdlname", (identfun)mdlname, "", ID_COMMAND, "");

static bool __dummy_rdvert_bool = addcommand("rdvert", (identfun)rdvert, "ffff", ID_COMMAND, "");

static bool __dummy_rdeye_bool = addcommand("rdeye", (identfun)rdeye, "i", ID_COMMAND, "");

static bool __dummy_rdtri_bool = addcommand("rdtri", (identfun)rdtri, "iii", ID_COMMAND, "");

static bool __dummy_rdjoint_bool = addcommand("rdjoint", (identfun)rdjoint, "iiiii", ID_COMMAND, "");

static bool __dummy_rdlimitdist_bool = addcommand("rdlimitdist", (identfun)rdlimitdist, "iiff", ID_COMMAND, "");

static bool __dummy_rdlimitrot_bool = addcommand("rdlimitrot", (identfun)rdlimitrot, "iifffff", ID_COMMAND, "");

static bool __dummy_rdanimjoints_bool = addcommand("rdanimjoints", (identfun)rdanimjoints, "i", ID_COMMAND, "");

static bool __dummy_mapmodel_bool = addcommand("mapmodel", (identfun)mapmodel, "s", ID_COMMAND, "");

static bool __dummy_mmodel_bool = addcommand("mmodel", (identfun)mmodel, "s", ID_COMMAND, "");

static bool __dummy_mapmodelreset_bool = addcommand("mapmodelreset", (identfun)mapmodelreset, "i", ID_COMMAND, "");

static bool __dummy_mapmodelname_bool = addcommand("mapmodelname", (identfun)mapmodelname_scriptimpl, "ii", ID_COMMAND, "");

static bool __dummy_nummapmodels_bool = addcommand("nummapmodels", (identfun)nummapmodels, "", ID_COMMAND, "");

static bool __dummy_clearmodel_bool = addcommand("clearmodel", (identfun)clearmodel, "s", ID_COMMAND, "");

static bool __dummy_findanims_bool = addcommand("findanims", (identfun)findanims, "s", ID_COMMAND, "");



    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = mdlcullface
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlcullface
    

    // cubeScriptProto = fff
    // cppArgumentTypes = ['float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c']
    // cppOriginalFunctionName = mdlcolor
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlcolor
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = mdlcollide
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlcollide
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = mdlellipsecollide
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlellipsecollide
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = mdltricollide
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdltricollide
    

    // cubeScriptProto = f
    // cppArgumentTypes = ['float *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['float * a']
    // cppOriginalFunctionName = mdlspec
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlspec
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = mdlgloss
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlgloss
    

    // cubeScriptProto = f
    // cppArgumentTypes = ['float *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['float * a']
    // cppOriginalFunctionName = mdlalphatest
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlalphatest
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = mdldepthoffset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdldepthoffset
    

    // cubeScriptProto = fff
    // cppArgumentTypes = ['float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c']
    // cppOriginalFunctionName = mdlglow
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlglow
    

    // cubeScriptProto = ffs
    // cppArgumentTypes = ['float *', 'float *', 'char *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'char * c']
    // cppOriginalFunctionName = mdlenvmap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlenvmap
    

    // cubeScriptProto = f
    // cppArgumentTypes = ['float *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['float * a']
    // cppOriginalFunctionName = mdlfullbright
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlfullbright
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = mdlshader
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlshader
    

    // cubeScriptProto = fff
    // cppArgumentTypes = ['float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c']
    // cppOriginalFunctionName = mdlspin
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlspin
    

    // cubeScriptProto = f
    // cppArgumentTypes = ['float *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['float * a']
    // cppOriginalFunctionName = mdlscale
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlscale
    

    // cubeScriptProto = fff
    // cppArgumentTypes = ['float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c']
    // cppOriginalFunctionName = mdltrans
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdltrans
    

    // cubeScriptProto = f
    // cppArgumentTypes = ['float *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['float * a']
    // cppOriginalFunctionName = mdlyaw
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlyaw
    

    // cubeScriptProto = f
    // cppArgumentTypes = ['float *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['float * a']
    // cppOriginalFunctionName = mdlpitch
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlpitch
    

    // cubeScriptProto = f
    // cppArgumentTypes = ['float *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['float * a']
    // cppOriginalFunctionName = mdlroll
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlroll
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = mdlshadow
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlshadow
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = mdlalphashadow
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlalphashadow
    

    // cubeScriptProto = fff
    // cppArgumentTypes = ['float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c']
    // cppOriginalFunctionName = mdlbb
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlbb
    

    // cubeScriptProto = fff
    // cppArgumentTypes = ['float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c']
    // cppOriginalFunctionName = mdlextendbb
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlextendbb
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = mdlname
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mdlname
    

    // cubeScriptProto = ffff
    // cppArgumentTypes = ['float *', 'float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c', 'float * d']
    // cppOriginalFunctionName = rdvert
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = rdvert
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = rdeye
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = rdeye
    

    // cubeScriptProto = iii
    // cppArgumentTypes = ['int *', 'int *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['int * a', 'int * b', 'int * c']
    // cppOriginalFunctionName = rdtri
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = rdtri
    

    // cubeScriptProto = iiiii
    // cppArgumentTypes = ['int *', 'int *', 'int *', 'int *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['int * a', 'int * b', 'int * c', 'int * d', 'int * e']
    // cppOriginalFunctionName = rdjoint
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = rdjoint
    

    // cubeScriptProto = iiff
    // cppArgumentTypes = ['int *', 'int *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'int * b', 'float * c', 'float * d']
    // cppOriginalFunctionName = rdlimitdist
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = rdlimitdist
    

    // cubeScriptProto = iifffff
    // cppArgumentTypes = ['int *', 'int *', 'float *', 'float *', 'float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
    // cppArgumentDecls = ['int * a', 'int * b', 'float * c', 'float * d', 'float * e', 'float * f', 'float * g']
    // cppOriginalFunctionName = rdlimitrot
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = rdlimitrot
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = rdanimjoints
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = rdanimjoints
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = mapmodel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mapmodel
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = mmodel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mmodel
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = mapmodelreset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mapmodelreset
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = mapmodelname_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mapmodelname
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = nummapmodels
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = nummapmodels
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = clearmodel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = clearmodel
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = findanims
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = findanims
    


