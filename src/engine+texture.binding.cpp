// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void texturereset(int * a);
extern void materialreset();
extern void decalreset(int * a);
extern void compactvslots_scriptimpl(int * a);
extern void fixinsidefaces_scriptimpl(int * a);
extern void texture(char * a, char * b, int * c, int * d, int * e, float * f);
extern void texgrass(char * a);
extern void texscroll(float * a, float * b);
extern void texoffset_scriptimpl(int * a, int * b);
extern void texrotate_scriptimpl(int * a);
extern void texscale(float * a);
extern void texlayer(int * a);
extern void texdetail(int * a);
extern void texalpha(float * a, float * b);
extern void texcolor(float * a, float * b, float * c);
extern void texrefract(float * a, float * b, float * c, float * d);
extern void texsmooth(int * a, int * b);
extern void decaldepth(float * a, float * b);
extern void reloadtex(char * a);
extern void gendds(char * a, char * b);
extern void screenshot(char * a);
extern void flipnormalmapy(char * a, char * b);
extern void mergenormalmaps(char * a, char * b);
extern void normalizenormalmap(char * a, char * b);
extern void removealphachannel(char * a, char * b);

static bool __dummy_texturereset_bool = addcommand("texturereset", (identfun)texturereset, "i", ID_COMMAND, "");

static bool __dummy_materialreset_bool = addcommand("materialreset", (identfun)materialreset, "", ID_COMMAND, "");

static bool __dummy_decalreset_bool = addcommand("decalreset", (identfun)decalreset, "i", ID_COMMAND, "");

static bool __dummy_compactvslots_bool = addcommand("compactvslots", (identfun)compactvslots_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_fixinsidefaces_bool = addcommand("fixinsidefaces", (identfun)fixinsidefaces_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_texture_bool = addcommand("texture", (identfun)texture, "ssiiif", ID_COMMAND, "");

static bool __dummy_texgrass_bool = addcommand("texgrass", (identfun)texgrass, "s", ID_COMMAND, "");

static bool __dummy_texscroll_bool = addcommand("texscroll", (identfun)texscroll, "ff", ID_COMMAND, "");

static bool __dummy_texoffset_bool = addcommand("texoffset", (identfun)texoffset_scriptimpl, "ii", ID_COMMAND, "");

static bool __dummy_texrotate_bool = addcommand("texrotate", (identfun)texrotate_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_texscale_bool = addcommand("texscale", (identfun)texscale, "f", ID_COMMAND, "");

static bool __dummy_texlayer_bool = addcommand("texlayer", (identfun)texlayer, "i", ID_COMMAND, "");

static bool __dummy_texdetail_bool = addcommand("texdetail", (identfun)texdetail, "i", ID_COMMAND, "");

static bool __dummy_texalpha_bool = addcommand("texalpha", (identfun)texalpha, "ff", ID_COMMAND, "");

static bool __dummy_texcolor_bool = addcommand("texcolor", (identfun)texcolor, "fff", ID_COMMAND, "");

static bool __dummy_texrefract_bool = addcommand("texrefract", (identfun)texrefract, "ffff", ID_COMMAND, "");

static bool __dummy_texsmooth_bool = addcommand("texsmooth", (identfun)texsmooth, "ii", ID_COMMAND, "");

static bool __dummy_decaldepth_bool = addcommand("decaldepth", (identfun)decaldepth, "ff", ID_COMMAND, "");

static bool __dummy_reloadtex_bool = addcommand("reloadtex", (identfun)reloadtex, "s", ID_COMMAND, "");

static bool __dummy_gendds_bool = addcommand("gendds", (identfun)gendds, "ss", ID_COMMAND, "");

static bool __dummy_screenshot_bool = addcommand("screenshot", (identfun)screenshot, "s", ID_COMMAND, "");

static bool __dummy_flipnormalmapy_bool = addcommand("flipnormalmapy", (identfun)flipnormalmapy, "ss", ID_COMMAND, "");

static bool __dummy_mergenormalmaps_bool = addcommand("mergenormalmaps", (identfun)mergenormalmaps, "ss", ID_COMMAND, "");

static bool __dummy_normalizenormalmap_bool = addcommand("normalizenormalmap", (identfun)normalizenormalmap, "ss", ID_COMMAND, "");

static bool __dummy_removealphachannel_bool = addcommand("removealphachannel", (identfun)removealphachannel, "ss", ID_COMMAND, "");



    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = texturereset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texturereset
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = materialreset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = materialreset
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = decalreset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = decalreset
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = compactvslots_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = compactvslots
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = fixinsidefaces_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fixinsidefaces
    

    // cubeScriptProto = ssiiif
    // cppArgumentTypes = ['char *', 'char *', 'int *', 'int *', 'int *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f']
    // cppArgumentDecls = ['char * a', 'char * b', 'int * c', 'int * d', 'int * e', 'float * f']
    // cppOriginalFunctionName = texture
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texture
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = texgrass
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texgrass
    

    // cubeScriptProto = ff
    // cppArgumentTypes = ['float *', 'float *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'float * b']
    // cppOriginalFunctionName = texscroll
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texscroll
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = texoffset_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texoffset
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = texrotate_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texrotate
    

    // cubeScriptProto = f
    // cppArgumentTypes = ['float *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['float * a']
    // cppOriginalFunctionName = texscale
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texscale
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = texlayer
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texlayer
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = texdetail
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texdetail
    

    // cubeScriptProto = ff
    // cppArgumentTypes = ['float *', 'float *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'float * b']
    // cppOriginalFunctionName = texalpha
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texalpha
    

    // cubeScriptProto = fff
    // cppArgumentTypes = ['float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c']
    // cppOriginalFunctionName = texcolor
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texcolor
    

    // cubeScriptProto = ffff
    // cppArgumentTypes = ['float *', 'float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c', 'float * d']
    // cppOriginalFunctionName = texrefract
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texrefract
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = texsmooth
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = texsmooth
    

    // cubeScriptProto = ff
    // cppArgumentTypes = ['float *', 'float *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'float * b']
    // cppOriginalFunctionName = decaldepth
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = decaldepth
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = reloadtex
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = reloadtex
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = gendds
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = gendds
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = screenshot
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = screenshot
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = flipnormalmapy
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = flipnormalmapy
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = mergenormalmaps
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mergenormalmaps
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = normalizenormalmap
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = normalizenormalmap
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = removealphachannel
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = removealphachannel
    


